# Stored Procedures
A stored procedure is a precompiled collection of SQL statements and procedural logic that is stored in a database and can be called by name. It's a powerful feature offered by database management systems (DBMS) that allows you to encapsulate and execute a set of SQL statements as a single unit of work.

Here are some key characteristics of stored procedures:

1. **Precompilation**: Stored procedures are precompiled and stored in the database, which can improve performance by reducing the overhead of parsing and optimizing SQL statements each time they are executed.

2. **Parametrization**: Stored procedures can accept parameters, allowing them to be more flexible and reusable. Parameters can be used to customize the behavior of the stored procedure at runtime.

3. **Procedural Logic**: In addition to SQL statements, stored procedures can contain procedural logic such as conditional statements (IF-ELSE), loops, error handling, and transaction control statements (BEGIN, COMMIT, ROLLBACK).

4. **Transaction Management**: Stored procedures can manage transactions, allowing you to perform multiple SQL operations as a single atomic unit. This ensures data integrity and consistency by either committing all changes or rolling them back if an error occurs.

5. **Security**: Stored procedures can help enforce security policies by controlling access to data and restricting the operations that users can perform. Database administrators can grant permissions to execute specific stored procedures while restricting direct access to tables or views.

6. **Encapsulation**: Stored procedures provide a way to encapsulate and centralize business logic within the database, promoting code reuse, reducing redundancy, and making it easier to maintain and update the codebase.

Overall, stored procedures are a valuable tool for building efficient, secure, and maintainable database-driven applications. They provide a way to encapsulate complex database operations and business logic, improving performance, security, and maintainability.


## Why Stored Procedures?

Stored procedures are used in databases for several reasons, including:

1. **Modularization of Logic**: Stored procedures allow you to encapsulate complex business logic and database operations into reusable modules. This modularization promotes code reuse, reduces redundancy, and makes it easier to maintain and update the codebase.

2. **Improved Performance**: By executing SQL statements on the database server rather than sending them over the network from the client application, stored procedures can improve performance. This is especially true for operations that involve complex computations or large datasets, as the processing is done closer to the data.

3. **Enhanced Security**: Stored procedures can help enforce security policies by controlling access to data and restricting the operations that users can perform. Database administrators can grant permissions to execute specific stored procedures while restricting direct access to tables or views.

4. **Transaction Management**: Stored procedures can be used to manage transactions, ensuring that multiple SQL statements are executed atomically. This helps maintain data integrity and consistency by guaranteeing that either all changes are committed or none of them are.

5. **Reduced Network Traffic**: By bundling multiple SQL statements into a single stored procedure call, you can reduce the amount of data transmitted between the database server and the client application. This can lead to significant reductions in network traffic, especially for applications with high concurrency or large datasets.

6. **Encapsulation of Business Logic**: Stored procedures provide a centralized location for defining and maintaining business rules and logic. This helps ensure consistency across applications and reduces the risk of logic errors or inconsistencies.

7. **Ease of Maintenance**: Since stored procedures are stored on the database server, they can be easily updated and version-controlled without requiring changes to client applications. This simplifies maintenance and deployment processes, especially in environments with multiple applications accessing the same database.

Overall, stored procedures are a valuable tool for improving the performance, security, and maintainability of database-driven applications. They provide a way to centralize and encapsulate database logic, leading to more efficient, secure, and maintainable software systems.

## Stored Procedure with Switch Statement
In MySQL, you can use a `CASE` or `IF` statement to implement conditional logic similar to a switch statement found in other programming languages. Let's see an example of using the `CASE` statement within a stored procedure:

Suppose we want to create a stored procedure that takes an input parameter `grade` (representing a student's grade) and returns a corresponding message based on the grade range.

Here's how you can achieve this using the `CASE` statement:

```sql
DELIMITER //

CREATE PROCEDURE GetGradeMessage(IN grade INT)
BEGIN
    DECLARE grade_message VARCHAR(255);

    CASE
        WHEN grade >= 90 THEN SET grade_message = 'Excellent';
        WHEN grade >= 80 THEN SET grade_message = 'Very Good';
        WHEN grade >= 70 THEN SET grade_message = 'Good';
        WHEN grade >= 60 THEN SET grade_message = 'Satisfactory';
        ELSE SET grade_message = 'Needs Improvement';
    END CASE;

    SELECT grade_message AS message;
END //

DELIMITER ;
```

In this stored procedure:

- We define a variable `grade_message` to store the message corresponding to the grade.
- We use the `CASE` statement to evaluate the value of the input parameter `grade` and set the `grade_message` variable accordingly based on the specified conditions.
- The `SELECT` statement is used to return the `grade_message` as the result of the stored procedure.

To call this stored procedure and retrieve the grade message:

```sql
CALL GetGradeMessage(85);
```

This will call the `GetGradeMessage` stored procedure with the grade value of 85, and it will return the message 'Very Good'.

You can modify the logic inside the `CASE` statement to suit your specific requirements. Additionally, you can use the `IF` statement instead of `CASE` for simpler conditional logic.


## Stored Procedure with IN OUT parameters
In MySQL, you can create stored procedures with parameters, including `IN`, `OUT`, and `INOUT` parameters. These parameters allow you to pass values into the stored procedure, receive values from the stored procedure, or both.

Here's how you can define a stored procedure with `IN`, `OUT`, and `INOUT` parameters:

```sql
DELIMITER //

CREATE PROCEDURE ExampleProcedure(
    IN in_param INT,
    OUT out_param VARCHAR(255),
    INOUT inout_param INT
)
BEGIN
    -- Process the IN parameter
    -- This is just an example, you can perform any operations here
    SET out_param = CONCAT('Input parameter value is: ', in_param);

    -- Process the INOUT parameter
    -- This is just an example, you can perform any operations here
    SET inout_param = inout_param * 2;
END //

DELIMITER ;
```

In this example:

- `in_param` is an `IN` parameter, which means it is passed into the stored procedure.
- `out_param` is an `OUT` parameter, which means it is returned from the stored procedure.
- `inout_param` is an `INOUT` parameter, which means it is both passed into and returned from the stored procedure.

To call this stored procedure and retrieve the `OUT` and `INOUT` parameters:

```sql
CALL ExampleProcedure(10, @out_value, @inout_value);
SELECT @out_value, @inout_value;
```

After executing this SQL statement, the `@out_value` variable will contain the value returned by the `out_param` parameter, and the `@inout_value` variable will contain the modified value of the `inout_param` parameter.

Keep in mind that you need to declare the output variables (`@out_value` and `@inout_value`) before calling the stored procedure to store the values returned by the `OUT` and `INOUT` parameters.


## Stored Procedure with Multiple OUT Parameters
In MySQL, you can define stored procedures with multiple output parameters to return multiple values from the procedure. Here's an example of how you can create a stored procedure with multiple output parameters:

Let's say we want to create a stored procedure that takes an employee ID as input and returns the employee's name, department, and salary as output parameters.

```sql
DELIMITER //

CREATE PROCEDURE GetEmployeeDetails(
    IN emp_id INT,
    OUT emp_name VARCHAR(255),
    OUT emp_department VARCHAR(255),
    OUT emp_salary DECIMAL(10, 2)
)
BEGIN
    -- Declare variables to store employee details
    DECLARE emp_name_var VARCHAR(255);
    DECLARE emp_department_var VARCHAR(255);
    DECLARE emp_salary_var DECIMAL(10, 2);
    
    -- Retrieve employee details based on emp_id
    SELECT name, department, salary INTO emp_name_var, emp_department_var, emp_salary_var
    FROM employees
    WHERE id = emp_id;
    
    -- Assign values to output parameters
    SET emp_name = emp_name_var;
    SET emp_department = emp_department_var;
    SET emp_salary = emp_salary_var;
END //

DELIMITER ;
```

In this example:

- The stored procedure `GetEmployeeDetails` takes an `IN` parameter `emp_id` representing the employee ID.
- It has three `OUT` parameters: `emp_name`, `emp_department`, and `emp_salary`, which will store the employee's name, department, and salary, respectively.
- Inside the procedure, variables (`emp_name_var`, `emp_department_var`, `emp_salary_var`) are declared to store the retrieved employee details temporarily.
- The `SELECT INTO` statement is used to fetch the employee details from the `employees` table based on the provided `emp_id`.
- Finally, the values of the temporary variables are assigned to the output parameters using the `SET` statement.

To call this stored procedure and retrieve the output parameters in MySQL:

```sql
CALL GetEmployeeDetails(123, @name, @department, @salary);
SELECT @name, @department, @salary;
```

This will call the `GetEmployeeDetails` stored procedure with an employee ID of 123 and retrieve the name, department, and salary of the employee into the user-defined variables `@name`, `@department`, and `@salary`, respectively.

## Stored Procedure with  Transaction

MySQL is a popular open-source relational database management system that supports stored procedures and transactions. Stored procedures allow you to group SQL statements into a reusable block of code, while transactions ensure that a group of SQL statements are executed as a single unit, either all successfully commit or all fail and roll back.

Here's how you can use stored procedures with transactions in MySQL:

1. **Creating a Stored Procedure**:
   You can create a stored procedure using the `CREATE PROCEDURE` statement in MySQL. Inside the stored procedure, you can define the SQL statements you want to execute.

   ```sql
   DELIMITER //
   CREATE PROCEDURE my_stored_procedure()
   BEGIN
       -- SQL statements
       SELECT * FROM my_table;
   END //
   DELIMITER ;
   ```

2. **Using Transactions**:
   Transactions in MySQL allow you to execute a group of SQL statements as a single unit of work. You can begin a transaction using the `START TRANSACTION` statement, perform SQL operations, and then either commit the changes using `COMMIT` or rollback the changes using `ROLLBACK`.

   ```sql
   START TRANSACTION;
   -- SQL statements
   INSERT INTO my_table (column1, column2) VALUES (value1, value2);
   UPDATE another_table SET column = value WHERE condition;
   -- Commit the transaction
   COMMIT;
   -- Or rollback the transaction
   ROLLBACK;
   ```

3. **Using Transactions with Stored Procedures**:
   You can combine stored procedures with transactions to encapsulate multiple SQL operations within a single transaction. Here's an example:

   ```sql
   DELIMITER //
   CREATE PROCEDURE my_stored_procedure_with_transaction()
   BEGIN
       -- Start the transaction
       START TRANSACTION;
       
       -- SQL statements within the transaction
       INSERT INTO my_table (column1, column2) VALUES (value1, value2);
       UPDATE another_table SET column = value WHERE condition;
       
       -- Commit or rollback the transaction based on conditions
       IF some_condition THEN
           COMMIT;
       ELSE
           ROLLBACK;
       END IF;
   END //
   DELIMITER ;
   ```

4. **Calling Stored Procedures**:
   Once you've created your stored procedure, you can call it using the `CALL` statement:

   ```sql
   CALL my_stored_procedure();
   ```

   You can also pass parameters to the stored procedure if needed.

By using stored procedures with transactions in MySQL, you can ensure data integrity and consistency by executing multiple SQL statements as a single atomic operation, making your database operations more robust and reliable.


## Cursor in Database

In MySQL and many other database systems, a cursor is a database object that enables the traversal of the result set of a query. Think of it as a pointer or a marker that moves through the rows of a result set one by one. 

Here's how it works:

1. **Fetching Rows**: When you execute a query in MySQL, it often returns multiple rows of data. A cursor allows you to fetch these rows one at a time, rather than fetching the entire result set at once.

2. **Sequential Access**: Cursors provide a way to sequentially access the rows of a result set. This means you can process each row individually, perform operations on it, and move to the next row until you reach the end of the result set.

3. **Processing Data**: Cursors are commonly used in stored procedures, triggers, and other database programming scenarios where you need to perform operations on each row of a result set programmatically.

4. **Control and Flexibility**: Cursors offer control and flexibility in navigating and manipulating result sets. They allow you to move forward, backward, or to specific rows within the result set, depending on your application's requirements.

However, it's important to note that excessive use of cursors can sometimes lead to performance issues, especially when dealing with large result sets, as they may involve additional overhead. So, while cursors provide powerful functionality, they should be used judiciously.


## Simple example of Cursor 
Let's walk through a simple example of how you might use a cursor in MySQL.

Suppose we have a table called `employees` with the following structure:

```sql
CREATE TABLE employees (
    id INT PRIMARY KEY,
    name VARCHAR(50),
    salary DECIMAL(10, 2)
);
```

And it contains some sample data:

```
+----+------------+--------+
| id | name       | salary |
+----+------------+--------+
|  1 | John       | 50000.00 |
|  2 | Alice      | 60000.00 |
|  3 | Bob        | 55000.00 |
+----+------------+--------+
```

Now, let's say we want to calculate the total salary of all employees. We can use a cursor to iterate through each row of the `employees` table and accumulate the salaries.

Here's how you might do it with a cursor in MySQL:

```sql
DELIMITER //

CREATE PROCEDURE calculate_total_salary()
BEGIN
    DECLARE total_salary DECIMAL(10, 2);
    DECLARE emp_salary DECIMAL(10, 2);
    
    -- Initialize total_salary
    SET total_salary = 0;

    -- Declare cursor for selecting employees
    DECLARE emp_cursor CURSOR FOR 
        SELECT salary FROM employees;

    -- Declare a NOT FOUND handler
    DECLARE CONTINUE HANDLER FOR NOT FOUND 
        SET done = TRUE;

    -- Open the cursor
    OPEN emp_cursor;

    -- Loop through each row
    emp_loop: LOOP
        -- Fetch the next row
        FETCH emp_cursor INTO emp_salary;
        
        -- Check if no more rows to fetch
        IF done THEN
            LEAVE emp_loop;
        END IF;
        
        -- Accumulate salary
        SET total_salary = total_salary + emp_salary;
    END LOOP;

    -- Close the cursor
    CLOSE emp_cursor;

    -- Output the total salary
    SELECT total_salary AS 'Total Salary';
END //

DELIMITER ;

-- Call the procedure
CALL calculate_total_salary();
```

In this example:

- We declare a cursor named `emp_cursor` to select the `salary` column from the `employees` table.
- We open the cursor and use a loop to fetch each row one by one.
- Inside the loop, we accumulate the salary of each employee into the `total_salary` variable.
- Once all rows are processed, we close the cursor and output the total salary.

This is a basic example of how you might use a cursor in MySQL to process rows of data from a table. Cursors can be handy for performing operations on individual rows or for more complex data processing tasks. However, keep in mind that they may not always be the most efficient solution, especially for large datasets.



## StoredProcedure with Multiple Cursors
In MySQL, you can work with multiple cursors within a stored procedure to fetch and process multiple result sets from queries. Here's an example of how you can create a stored procedure that uses multiple cursors:

Let's say we have a database with two tables: `employees` and `departments`. We want to create a stored procedure that fetches data from both tables using two separate cursors and then processes the data.

```sql
DELIMITER //

CREATE PROCEDURE ProcessEmployeeAndDepartment()
BEGIN
    -- Declare variables for employee and department details
    DECLARE emp_id INT;
    DECLARE emp_name VARCHAR(255);
    DECLARE dept_id INT;
    DECLARE dept_name VARCHAR(255);

    -- Declare cursor for fetching employee details
    DECLARE emp_cursor CURSOR FOR
        SELECT id, name FROM employees;

    -- Declare cursor for fetching department details
    DECLARE dept_cursor CURSOR FOR
        SELECT id, name FROM departments;

    -- Open the cursors
    OPEN emp_cursor;
    OPEN dept_cursor;

    -- Fetch and process employee details
    employee_loop: LOOP
        FETCH emp_cursor INTO emp_id, emp_name;
        IF emp_id IS NULL THEN
            LEAVE employee_loop;
        END IF;
        
        -- Process employee details
        -- For example, print employee details
        SELECT CONCAT('Employee: ', emp_name);
    END LOOP;

    -- Fetch and process department details
    department_loop: LOOP
        FETCH dept_cursor INTO dept_id, dept_name;
        IF dept_id IS NULL THEN
            LEAVE department_loop;
        END IF;
        
        -- Process department details
        -- For example, print department details
        SELECT CONCAT('Department: ', dept_name);
    END LOOP;

    -- Close the cursors
    CLOSE emp_cursor;
    CLOSE dept_cursor;
END //

DELIMITER ;
```

In this stored procedure:

- We declare variables to store employee and department details (`emp_id`, `emp_name`, `dept_id`, `dept_name`).
- We declare two cursors (`emp_cursor` and `dept_cursor`) to fetch data from the `employees` and `departments` tables, respectively.
- We open the cursors using the `OPEN` statement.
- We fetch data from each cursor using a loop (`employee_loop` and `department_loop`) and process the data as needed.
- Finally, we close the cursors using the `CLOSE` statement.

To call this stored procedure:

```sql
CALL ProcessEmployeeAndDepartment();
```

This will execute the stored procedure, fetch data from both tables using cursors, and process the data accordingly. Adjust the processing logic inside the loops as per your requirements.


## Stored Procedure with Multiple cursors working parallely
In MySQL, stored procedures can update multiple tables in parallel using multiple cursors. However, it's essential to understand that MySQL does not support parallel execution of statements within a single connection. Therefore, the updates to different tables in a stored procedure would be sequential, not parallel.

Here's an example of a stored procedure that updates multiple tables using multiple cursors:

Suppose we have two tables: `employees` and `departments`. We want to create a stored procedure that updates both tables simultaneously.

```sql
DELIMITER //

CREATE PROCEDURE UpdateEmployeeAndDepartment(IN emp_id INT, IN new_salary DECIMAL(10,2), IN new_department_id INT)
BEGIN
    DECLARE emp_cursor CURSOR FOR
        SELECT id, salary FROM employees WHERE id = emp_id;

    DECLARE dept_cursor CURSOR FOR
        SELECT id FROM departments WHERE id = new_department_id;

    DECLARE emp_found BOOLEAN DEFAULT FALSE;
    DECLARE dept_found BOOLEAN DEFAULT FALSE;

    OPEN emp_cursor;
    FETCH emp_cursor INTO emp_id, emp_salary;
    IF FOUND_ROWS() > 0 THEN
        SET emp_found := TRUE;
    END IF;
    CLOSE emp_cursor;

    OPEN dept_cursor;
    FETCH dept_cursor INTO dept_id;
    IF FOUND_ROWS() > 0 THEN
        SET dept_found := TRUE;
    END IF;
    CLOSE dept_cursor;

    IF emp_found AND dept_found THEN
        START TRANSACTION;
        UPDATE employees SET salary = new_salary WHERE id = emp_id;
        UPDATE employees SET department_id = new_department_id WHERE id = emp_id;
        COMMIT;
    ELSE
        SELECT 'Employee or Department not found';
    END IF;
END //

DELIMITER ;
```

In this stored procedure:

- We declare two cursors, `emp_cursor` and `dept_cursor`, to fetch data from the `employees` and `departments` tables, respectively.
- We open and fetch data from each cursor to check if the employee and department exist.
- If both the employee and department exist, we update the `employees` table to change the salary and department ID for the given employee.
- We use transactions (`START TRANSACTION` and `COMMIT`) to ensure that the updates to both tables are atomic.

To call this stored procedure:

```sql
CALL UpdateEmployeeAndDepartment(123, 50000.00, 2);
```

This will update the salary and department ID for the employee with ID 123 in the `employees` table. Adjust the procedure according to your specific requirements and table structures.


## Advantages and Disadvantages of using Cursor

In the context of databases, a cursor is a database object that allows manipulation of database result sets one row at a time. Here are some advantages and disadvantages of using cursors:

Advantages:

1. **Row-Level Processing**: Cursors enable row-level processing, allowing developers to manipulate each row individually, which can be useful for complex data processing tasks.

2. **Customized Processing**: Cursors provide flexibility in processing data by allowing developers to define custom logic for fetching, updating, and deleting rows.

3. **Navigation Control**: Cursors offer precise control over navigation through the result set, allowing developers to move forward, backward, or to a specific row as needed.

4. **Memory Management**: Cursors can help manage memory efficiently, particularly in situations where the result set is large and cannot be loaded entirely into memory at once.

Disadvantages:

1. **Performance Overhead**: Cursors can incur performance overhead, especially when processing large result sets, as they require additional resources for maintaining state and processing each row individually.

2. **Locking and Blocking**: Cursors may hold locks on rows or tables for an extended period, potentially causing blocking issues for other concurrent transactions trying to access the same data.

3. **Resource Consumption**: Cursors consume server resources such as memory and CPU, particularly if they are left open for an extended period, which can impact the overall performance of the database server.

4. **Complexity and Error-Prone**: Working with cursors introduces complexity into the code, increasing the likelihood of errors such as resource leaks, cursor not being closed properly, and incorrect handling of exceptions.

5. **Limited Scalability**: The use of cursors can limit the scalability of the application, especially in distributed or highly concurrent environments, where managing resources efficiently becomes critical.

6. **Suboptimal for Set-Based Operations**: Cursors are primarily designed for row-level processing and may not be the most efficient solution for set-based operations, which are better suited for SQL's declarative nature.

In summary, while cursors offer flexibility and control over row-level processing, they also come with performance overhead and complexity. It's essential to weigh the advantages against the disadvantages and consider alternative approaches, such as set-based operations, wherever possible to optimize database performance and scalability.