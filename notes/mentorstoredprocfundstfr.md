##  Stored Procedure – Fund Transfer in Banking DB

### 🧭 **Real-World Problem:**

**Banking System → Fund Transfer**

> 🧑‍💼 “A customer wants to transfer ₹1000 from one account to another. Can we do it correctly, securely, and in one transaction?”


### 💡 Business Logic Breakdown (Mentor thinking aloud)

| Step | Logic                                           |
| ---- | ----------------------------------------------- |
| 1️⃣  | **Check source account balance**                |
| 2️⃣  | **If balance is sufficient**, then              |
| 3️⃣  | Subtract amount from source account             |
| 4️⃣  | Add amount to destination account               |
| 5️⃣  | Record transaction in `operations` table        |
| 6️⃣  | Set transaction status = 'COMPLETED'            |
| 7️⃣  | If balance insufficient → Set status = 'FAILED' |

 

### 🛠️ SQL Procedure with Variables: Code Walkthrough

```sql
DELIMITER //

CREATE PROCEDURE sp_transfer_funds (
    IN p_from_account INT,
    IN p_to_account INT,
    IN p_amount DECIMAL(10,2)
)
BEGIN
    DECLARE v_source_balance DECIMAL(10,2);
    DECLARE v_destination_balance DECIMAL(10,2);

    -- Step 1: Get source account balance
    SELECT balance INTO v_source_balance
    FROM accounts
    WHERE account_id = p_from_account;

    -- Step 2: Check if source has enough balance
    IF v_source_balance >= p_amount THEN
        -- Step 3: Debit from source
        UPDATE accounts
        SET balance = balance - p_amount
        WHERE account_id = p_from_account;

        -- Step 4: Credit to destination
        UPDATE accounts
        SET balance = balance + p_amount
        WHERE account_id = p_to_account;

        -- Step 5: Insert into operations log
        INSERT INTO operations (
            from_account,
            to_account,
            amount,
            operation_date,
            status
        )
        VALUES (
            p_from_account,
            p_to_account,
            p_amount,
            NOW(),
            'COMPLETED'
        );
    ELSE
        -- Step 6: Insert failed attempt into operations
        INSERT INTO operations (
            from_account,
            to_account,
            amount,
            operation_date,
            status
        )
        VALUES (
            p_from_account,
            p_to_account,
            p_amount,
            NOW(),
            'FAILED'
        );
    END IF;
END;
//

DELIMITER ;
```
### 🧪 How to Test This

```sql
CALL sp_transfer_funds(101, 202, 1000);
SELECT * FROM operations;
```

### 🧠 Mentor Insights During Story

| Insight           | Analogy / Message                                                 |
| ----------------- | ----------------------------------------------------------------- |
| DECLARE variables | Kitchen bowls – hold temp values during cooking                   |
| IF check          | "Do we have enough money to buy this item?"                       |
| UPDATE logic      | Like withdrawing and depositing at a bank                         |
| INSERT log        | Entry in bank passbook                                            |
| Status flag       | Like a receipt: 'COMPLETED' or 'FAILED'                           |
| Delimiters        | Change command ending when writing multiline SP                   |
| Error learning    | "Coding is correction" – logical debugging improves understanding |
| Creativity        | "Don't memorize, understand and recreate"                         |
| Parameter naming  | Use `p_` for parameters, `v_` for local variables for clarity     |

### 🔁 Key Concepts Recap

* ✅ `DECLARE` variables to hold temporary data
* ✅ Use `SELECT ... INTO` for assigning values from queries
* ✅ Perform conditional logic using `IF ... THEN ... ELSE`
* ✅ Track operations for **audit trail**
* ✅ Store procedures bring **reusability**, **security**, and **performance**

### 🎯 Student Exercise (Inspired by Session)

Create the following procedures:

1. `sp_deposit_funds(p_account_id, p_amount)`
2. `sp_withdraw_funds(p_account_id, p_amount)`
3. `sp_get_account_statement(p_account_id)`
