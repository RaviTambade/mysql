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
