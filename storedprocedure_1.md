# More Stored Produre Examples :OrderProcessing

Let’s explore some examples of stored procedures for order processing operations in MySQL. We'll cover common tasks such as placing an order, updating order status, calculating order totals, and handling order history.

### Example 1: Placing an Order

This example demonstrates a stored procedure to place an order. It will update the inventory and create an order record.

#### Create Tables

```sql
-- Create the Inventory table
CREATE TABLE Inventory (
    ProductID INT PRIMARY KEY,
    ProductName VARCHAR(100) NOT NULL,
    Quantity INT NOT NULL,
    UnitPrice DECIMAL(10, 2) NOT NULL
);

-- Create the Orders table
CREATE TABLE Orders (
    OrderID INT AUTO_INCREMENT PRIMARY KEY,
    OrderDate DATETIME DEFAULT CURRENT_TIMESTAMP,
    CustomerName VARCHAR(100) NOT NULL,
    TotalAmount DECIMAL(10, 2) NOT NULL
);

-- Create the OrderDetails table
CREATE TABLE OrderDetails (
    OrderDetailID INT AUTO_INCREMENT PRIMARY KEY,
    OrderID INT,
    ProductID INT,
    Quantity INT,
    UnitPrice DECIMAL(10, 2),
    FOREIGN KEY (OrderID) REFERENCES Orders(OrderID),
    FOREIGN KEY (ProductID) REFERENCES Inventory(ProductID)
);
```

#### Create Stored Procedure

```sql
DELIMITER //

CREATE PROCEDURE PlaceOrder(
    IN p_CustomerName VARCHAR(100),
    IN p_OrderItems JSON
)
BEGIN
    DECLARE v_OrderID INT;
    DECLARE v_ProductID INT;
    DECLARE v_Quantity INT;
    DECLARE v_UnitPrice DECIMAL(10, 2);
    DECLARE v_TotalAmount DECIMAL(10, 2) DEFAULT 0;
    DECLARE v_ItemCount INT;
    DECLARE i INT DEFAULT 0;

    -- Start a transaction
    START TRANSACTION;

    -- Insert a new order
    INSERT INTO Orders (CustomerName, TotalAmount)
    VALUES (p_CustomerName, 0);

    -- Get the generated OrderID
    SET v_OrderID = LAST_INSERT_ID();

    -- Get the number of items in the JSON array
    SET v_ItemCount = JSON_LENGTH(p_OrderItems);

    -- Loop through each item in the JSON array
    WHILE i < v_ItemCount DO
        -- Extract item details
        SET v_ProductID = JSON_EXTRACT(p_OrderItems, CONCAT('$[', i, '].ProductID'));
        SET v_Quantity = JSON_EXTRACT(p_OrderItems, CONCAT('$[', i, '].Quantity'));

        -- Get the unit price of the product
        SELECT UnitPrice INTO v_UnitPrice
        FROM Inventory
        WHERE ProductID = v_ProductID;

        -- Check if sufficient quantity is available
        IF v_Quantity > (SELECT Quantity FROM Inventory WHERE ProductID = v_ProductID) THEN
            SIGNAL SQLSTATE '45000' SET MESSAGE_TEXT = CONCAT('Insufficient quantity for ProductID ', v_ProductID);
        END IF;

        -- Update inventory
        UPDATE Inventory
        SET Quantity = Quantity - v_Quantity
        WHERE ProductID = v_ProductID;

        -- Insert order details
        INSERT INTO OrderDetails (OrderID, ProductID, Quantity, UnitPrice)
        VALUES (v_OrderID, v_ProductID, v_Quantity, v_UnitPrice);

        -- Update total amount
        SET v_TotalAmount = v_TotalAmount + (v_Quantity * v_UnitPrice);

        SET i = i + 1;
    END WHILE;

    -- Update order total amount
    UPDATE Orders
    SET TotalAmount = v_TotalAmount
    WHERE OrderID = v_OrderID;

    -- Commit the transaction
    COMMIT;
END //

DELIMITER ;
```

#### Example Usage

To place an order with a JSON array of items:

```sql
CALL PlaceOrder('John Doe', '[{"ProductID":1, "Quantity":2}, {"ProductID":2, "Quantity":1}]');
```

### Example 2: Updating Order Status

This example demonstrates a stored procedure to update the status of an order.

#### Create Orders Table with Status

```sql
-- Alter Orders table to include status
ALTER TABLE Orders ADD COLUMN Status VARCHAR(50) DEFAULT 'Pending';
```

#### Create Stored Procedure

```sql
DELIMITER //

CREATE PROCEDURE UpdateOrderStatus(
    IN p_OrderID INT,
    IN p_Status VARCHAR(50)
)
BEGIN
    -- Update order status
    UPDATE Orders
    SET Status = p_Status
    WHERE OrderID = p_OrderID;

    -- Check if the update was successful
    IF ROW_COUNT() = 0 THEN
        SIGNAL SQLSTATE '45000' SET MESSAGE_TEXT = 'OrderID does not exist.';
    END IF;
END //

DELIMITER ;
```

#### Example Usage

To update the status of an order:

```sql
CALL UpdateOrderStatus(1, 'Shipped');
```

### Example 3: Calculating Total Order Value

This example calculates the total value of all orders for a specific customer.

#### Create Stored Procedure

```sql
DELIMITER //

CREATE PROCEDURE CalculateCustomerOrderTotal(
    IN p_CustomerName VARCHAR(100)
)
BEGIN
    DECLARE v_TotalValue DECIMAL(10, 2);

    -- Calculate total value of all orders for the customer
    SELECT SUM(TotalAmount) INTO v_TotalValue
    FROM Orders
    WHERE CustomerName = p_CustomerName;

    -- Return the total value
    SELECT v_TotalValue AS TotalOrderValue;
END //

DELIMITER ;
```

#### Example Usage

To calculate the total order value for a customer:

```sql
CALL CalculateCustomerOrderTotal('John Doe');
```

### Example 4: Viewing Order History

This example retrieves the history of orders including their details.

#### Create Stored Procedure

```sql
DELIMITER //

CREATE PROCEDURE GetOrderHistory(
    IN p_OrderID INT
)
BEGIN
    -- Retrieve order details
    SELECT o.OrderID, o.OrderDate, o.CustomerName, o.TotalAmount, o.Status,
           d.ProductID, i.ProductName, d.Quantity, d.UnitPrice
    FROM Orders o
    JOIN OrderDetails d ON o.OrderID = d.OrderID
    JOIN Inventory i ON d.ProductID = i.ProductID
    WHERE o.OrderID = p_OrderID;
END //

DELIMITER ;
```

#### Example Usage

To view the history of a specific order:

```sql
CALL GetOrderHistory(1);
```

### Summary

These stored procedures cover a range of order processing operations:
1. **Placing an Order**: Handles inventory updates and order details.
2. **Updating Order Status**: Changes the status of an existing order.
3. **Calculating Total Order Value**: Computes the total value of all orders for a specific customer.
4. **Viewing Order History**: Retrieves details of a specific order, including product information.

Each example demonstrates different aspects of order management and how you can use MySQL stored procedures to handle complex business logic. Feel free to adapt these examples to your specific requirements or expand them with additional functionality.