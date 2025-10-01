## 📘 Database Transactions in Banking

👨‍🏫 *Mentor’s Voice:*

“Imagine you are a **bank database administrator**. One day, a customer comes to the bank and wants to **transfer ₹10,000 from their savings account to a friend’s account**.

Now, let’s pause and think: **what are the steps behind the scenes?**

1. Deduct ₹10,000 from Customer A’s account.
2. Add ₹10,000 to Customer B’s account.

Seems simple, right?

But here’s the problem: what if something goes wrong **after step 1**?

* Maybe the bank server crashes.
* Maybe there’s a network issue.

If step 1 is completed (money deducted) but step 2 is **not completed** (money not added), the bank loses money.

This is where **database transactions** come into play — they ensure **all steps succeed together or fail together**. This is called **atomicity**.


## 🔹 Step 1: Create Banking Table

```sql
CREATE DATABASE bankDB;
USE bankDB;

CREATE TABLE accounts (
    account_id INT PRIMARY KEY,
    name VARCHAR(50),
    balance DECIMAL(10,2)
);

-- Insert two sample accounts
INSERT INTO accounts (account_id, name, balance) VALUES (1, 'Ravi', 50000);
INSERT INTO accounts (account_id, name, balance) VALUES (2, 'Tejas', 30000);
```

## 🔹 Step 2: Transfer Money WITHOUT Transaction (Unsafe)

```sql
-- Step 1: Deduct from Ravi
UPDATE accounts SET balance = balance - 10000 WHERE account_id = 1;

-- Step 2: Add to Tejas
UPDATE accounts SET balance = balance + 10000 WHERE account_id = 2;
```

👨‍🏫 *Mentor’s Note:*
“If the server crashes **after the first UPDATE**, Ravi’s account is debited but Tejas doesn’t get the money. Disaster!”

## 🔹 Step 3: Transfer Money WITH Transaction (Safe)

```sql
-- Start a transaction
START TRANSACTION;

-- Step 1: Deduct from Ravi
UPDATE accounts SET balance = balance - 10000 WHERE account_id = 1;

-- Step 2: Add to Tejas
UPDATE accounts SET balance = balance + 10000 WHERE account_id = 2;

-- Commit the transaction
COMMIT;
```

👨‍🏫 *Mentor’s Note:*
“This ensures **all steps succeed together**.

* If everything goes well → COMMIT saves the changes permanently.
* If something goes wrong → ROLLBACK can cancel all steps and restore original balances.

## 🔹 Step 4: Simulate a Failure

```sql
START TRANSACTION;

UPDATE accounts SET balance = balance - 10000 WHERE account_id = 1;

-- Oops! Something goes wrong
ROLLBACK;  -- cancels the deduction

SELECT * FROM accounts;
```

✅ Output: Both balances remain unchanged.

## 🔹 Step 5: Key Concepts in Transactions

1. **ACID properties** – the backbone of transactions:

   * **A**tomicity → All steps succeed or fail together.
   * **C**onsistency → Database remains in a valid state.
   * **I**solation → Transactions don’t interfere with each other.
   * **D**urability → Once committed, data is permanently saved.

2. **COMMIT** → Save all changes permanently.

3. **ROLLBACK** → Undo all changes in the transaction.

## 🔹 Mentor’s Analogy:

“Think of a transaction like **moving money in a sealed envelope**:

* You can only send the envelope when **both sender and receiver are ready**.
* If anything goes wrong mid-way, you can **stop and return the envelope**.
* No money is ever lost, and both accounts stay correct.”

💡 **Tip for students:**
Whenever you perform **critical operations like bank transfers, order payments, or stock updates**, always use **transactions** to protect data integrity.
