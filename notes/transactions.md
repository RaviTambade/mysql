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



###  **The Tale of Two Shopkeepers**

Imagine two shopkeepers — **Ravi** and **Raj** — who run a bookstore where hundreds of customers visit daily.

#### 🛒 Scene 1: Ravi – The Optimist

Ravi believes most customers are honest and trustworthy. He lets customers pick books freely, write their details in a notebook, and trusts that no two customers will pick the exact same book at the same time.

He tells them:

> “Go ahead, take the book, write your name. When you're done, bring it back and I’ll note the sale."

Once a customer returns to the counter, Ravi checks:

* *Is the book still available?*
* *Has another customer taken it already?*
* *Has anything changed in the stock?*

If yes, he says:

> “Oh no! Someone just took the last copy while you were browsing. You’ll need to recheck.”

This is **Optimistic Locking**. It trusts that conflicts will **rarely occur**, and checks **only at the time of update**. Efficient, but needs **retry logic**.


#### 🔐 Scene 2: Raj – The Cautious One

Raj is more careful. He believes that with so many customers, **conflicts are bound to happen**. So, when someone wants a book:

He says:

> “Hold on, let me **reserve** this book for you. Until you decide, **no one else** can touch this.”

Only after the customer decides — buys or leaves — does Raj unlock the book for others.

This is **Pessimistic Locking**. It **locks the resource early**, ensuring no one else can change it. Safe, but could make other customers wait.


### 🧪 Real-Life Database Analogy

#### 🧠 Optimistic Locking in SQL Server

* Think of it like versioning. You fetch a record with a `Version` column.
* When you update it, SQL Server checks:

  > “Has the version changed? If yes, abort. If not, go ahead.”

**SQL Code**:

```sql
-- Fetch record
SELECT Name, Version FROM Products WHERE ProductID = 1;

-- Later, during update
UPDATE Products
SET Name = 'New Name'
WHERE ProductID = 1 AND Version = @OldVersion;
```

If another user already updated the product, the version will mismatch. You'll have to **retry**.


#### 🔒 Pessimistic Locking in SQL Server

* Think of it as putting a “Do Not Touch” tag on a row.
* SQL Server places an **exclusive lock** when reading the data.

**SQL Code**:

```sql
BEGIN TRANSACTION;

-- Lock the row
SELECT Name FROM Products WITH (XLOCK) WHERE ProductID = 1;

-- Perform update
UPDATE Products SET Name = 'New Name' WHERE ProductID = 1;

COMMIT;
```

No one else can even read that row until you finish. Safe, but **others must wait**.


### ⚖️ Mentor’s Wisdom: When to Choose What?

#### 🟢 Optimistic Locking:

Use when:

* Conflicts are **rare**.
* You want **maximum performance**.
* You're okay with **retrying on failure**.

🧩 **Examples**:

* Online surveys
* Customer profile updates
* Shopping cart updates

#### 🔴 Pessimistic Locking:

Use when:

* Data integrity is **mission-critical**.
* Conflicts are **frequent** or **dangerous**.
* You want **absolute safety**.

🧩 **Examples**:

* Banking systems
* Inventory deduction in warehouse
* Ticket booking systems


### 🧾 Mentor’s Summary Table

| Feature           | Optimistic Locking            | Pessimistic Locking                    |
| ----------------- | ----------------------------- | -------------------------------------- |
| Strategy          | **Trust**: Assume no conflict | **Caution**: Assume conflict is likely |
| Locking           | No locks during read          | Lock is applied immediately on read    |
| Concurrency       | High                          | Lower due to waiting                   |
| Conflict Handling | At update, may require retry  | Prevented upfront                      |
| Complexity        | Higher (needs retry logic)    | Lower (conflict avoided)               |
| Deadlock Risk     | Low                           | Higher                                 |
| Use Case          | Social apps, reports          | Banking, stock systems                 |

---

### 💬 Mentor’s Final Advice:

> **“When choosing between Optimistic and Pessimistic locking, ask yourself: How valuable is consistency vs. speed in my application? Am I ready to handle retries or prefer to block conflicts right away?”**

Understanding this balance will help you become a better system designer — one who respects the **art of concurrency**.
