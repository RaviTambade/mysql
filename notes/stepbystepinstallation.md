## MySQL  Ready Steady Go...

🎬 **Scene 1: The Beginning**
You’re sitting with your laptop. You know that you want to learn databases — not just storing data, but also understanding how real-world applications talk to a database server.
So the first tool you need is **MySQL Server**. And along with it, a friendly helper called **MySQL Workbench**, which gives you a nice graphical user interface (GUI) instead of only typing commands.

Think of **MySQL Server** as the *engine running in the background* 🚂 and **Workbench** as the *driver’s cabin controls* 🎛️ that let you steer the train.



🎬 **Scene 2: The Download Journey**
I tell you: *“Open Google. Type ‘MySQL Server for Windows download’.”*
You see the official **MySQL website** appear. There’s an option: **MySQL Installer 8.0 for Windows**.

Now, two versions are usually available:

* The small web installer (~2 MB, downloads components as needed).
* The big offline installer (~350 MB, contains everything).

Since you don’t want to worry about the internet later, we pick the **big installer (350 MB)**. You click:
👉 *“No thanks, just start my download.”*

And now… the `.msi` file lands safely in your **Downloads** folder.



🎬 **Scene 3: Installation Adventure**
Double-click that `.msi`. The **MySQL Installer** window appears — this is like a wizard guiding you through steps.

The wizard asks: *“What do you want to install?”*

* Only the **server** (background database engine)?
* Only the **client** (Workbench)?
* Or **everything**?

Being ambitious learners, we choose **Full Installation** ✅.
This installs:

* **MySQL Server 8.0.41**
* **MySQL Workbench** (GUI)
* **MySQL Shell** (command-line tool)
* Plus documentation and examples.

You click *Next → Execute → Next*. Slowly, a progress bar fills, showing each component being installed.



🎬 **Scene 4: Root Password & Configuration**
Now comes the important moment: the wizard asks for the **root password**.
This is like the *master key 🔑* to your database. Without it, nobody can enter.
Let’s say you set the password to **password** (in practice, you should set something stronger).

Next, the installer reminds you:

* The server will run on **port 3306** by default.
* It will keep running in the background as a Windows **Service** (like a silent worker).

You click *Next → Execute → Finish*.

Congratulations 🎉 — your **MySQL Server** is alive!



🎬 **Scene 5: Testing the Connection**
After finishing, **MySQL Workbench** opens automatically.
On the left, you see **Local Instance MySQL 8.0**. Click it.

It asks for your **root password**. You type it, click OK, and boom — the connection is successful.
Now you see a dashboard where you can create databases, tables, and run SQL queries.



🎬 **Scene 6: Behind the Scenes**
I ask you: *“Do you realize that while you’re seeing Workbench, something else is happening in the background?”*

👉 The **MySQL Server** process is quietly running as a Windows **Service**.
To see it:

* Press **Win + S** and search for **Services**.
* Scroll down until you see **MySQL80**.
* Its status says: **Running** ✅.

That’s your background engine. You can even **Stop / Pause / Restart** it from here — just like switching a car engine off and on.



🎬 **Scene 7: Understanding the Picture**
Let’s visualize it.

* **Your Computer Hardware** → Processor, RAM, Disk.
* **Operating System (Windows 10/11)** on top.
* **MySQL Server (background service)** listening on **port 3306**.
* **MySQL Workbench (GUI)** installed on top, helping you talk to the server.

Inside the server, you will create multiple **databases**:

* Example: *E-Commerce* database, *Student Information System* database.
  Each database will contain **tables** like:
* *Products* (id, name, price)
* *Customers* (id, name, email)

Tables contain **rows (records)**, where your actual data lives.
Whenever you type a query in Workbench, it goes to the **server**, which processes it and gives the result back.



🎬 **Scene 8: The Role of a DBA**
Now I tell you:

* A **Database Administrator (DBA)** can use either **Workbench (GUI)** or **MySQL Shell (CLI)**.
* They log in with the **root account** (or other user accounts you create).
* They manage databases, users, permissions, backups, etc.

So you’ve not just installed MySQL — you’ve opened the door to becoming a DBA or backend developer.



✅ **Summary (Mentor’s Key Notes):**

1. Download **MySQL Installer for Windows** (350 MB).
2. Choose **Full Installation** (Server + Workbench + Shell).
3. Set up **root password**.
4. Server runs as **Windows Service** on **port 3306**.
5. Use **Workbench** (GUI) or **Shell** (CLI) to interact.
6. Databases → Tables → Records → Queries.



🎬 **Scene 1: The Pause in the Engine**
I tell you: *“Look, the MySQL server is like the engine of a car 🚗. When it’s running, Workbench can talk to it. But what happens if we stop the engine?”*

So we go into **Windows Services** → find **MySQL80** → click **Stop**.
Now the status says ❌ **Stopped**.

Then we return to **MySQL Workbench** and try to connect again.

* What happens? A red error message appears at the bottom: *“No connection established.”*
* Why? Because the **server process isn’t running in the background**. Workbench is just a GUI — without the server, it’s like a steering wheel with no engine connected.



🎬 **Scene 2: Bringing the Engine Back**
Now I guide: *“Let’s start it again.”*
We right-click on **MySQL80** service → click **Start**.

Back in Workbench, we refresh the **Server Status**. This time it shows ✅ **Running** in green.
Now, once again, Workbench can connect successfully.
Moral: *If the server service is stopped, you cannot access databases. The Workbench depends on the server.*


🎬 **Scene 3: First Steps as a Database Administrator**
I say: *“Now that your server is running, let’s behave like a real Database Administrator (DBA).”*

From Workbench, you go to **Database → Connect to Database**.
Enter your root password → the connection opens.
Now we’re inside the world of MySQL.



🎬 **Scene 4: Exploring What Exists**
We run our first SQL command:

```sql
SHOW DATABASES;
```

Click the lightning icon ⚡ to execute.
We see system databases:

* `information_schema`
* `mysql`
* `performance_schema`
* `sys`

These are default schemas created by MySQL.



🎬 **Scene 5: Creating Our Own Database**
I say: *“Now, let’s make our own database — suppose we are building a small shop app.”*

Command:

```sql
CREATE DATABASE TFL_Store;
```

Execute → ✅ Message says *“Database created.”*

Check again with:

```sql
SHOW DATABASES;
```

Now we see `TFL_Store` added. But it’s empty — no tables yet.



🎬 **Scene 6: Selecting & Preparing It**
We tell MySQL: *“Hey, from now on, whatever I create or query, use this database.”*

```sql
USE TFL_Store;
```

The console replies: *“Database changed.”*
This is like saying, *“I walked into the TFL Store room.”*


🎬 **Scene 7: Creating Our First Table**
I explain: *“Now let’s create a table to store student information.”*

Command:

```sql
CREATE TABLE Students (
    ID INT,
    FirstName VARCHAR(50),
    LastName VARCHAR(50),
    Birth_Date DATE,
    Email VARCHAR(100),
    Phone_Number VARCHAR(10)
);
```

Execute → ✅ *“Query OK, table created.”*

Check with:

```sql
SHOW TABLES;
```

Result: `Students` 🎉



🎬 **Scene 8: Adding Our First Record**
Now we add data into our Students table.

```sql
INSERT INTO Students 
VALUES (1, 'Pranav', 'Sharma', '2001-05-20', 'pranav@gmail.com', '9876543210');
```

Execute → ✅ *“1 row inserted.”*



🎬 **Scene 9: Checking the Data**
We query back to confirm:

```sql
SELECT * FROM Students;
```

Result:

| ID | FirstName | LastName | Birth_Date | Email                                       | Phone_Number |
| -- | --------- | -------- | ---------- | ------------------------------------------- | ------------ |
| 1  | Pranav    | Sharma   | 2001-05-20 | [pranav@gmail.com](mailto:pranav@gmail.com) | 9876543210   |

👏 There it is — our first student record, safely stored in MySQL.



🎬 **Scene 10: The Big Realization**
I turn to you and say:
*“Notice something? We didn’t write `fopen`, `fwrite`, `fread` like in C programming. We didn’t build our own storage logic. Instead, we used a ready-made, powerful system — MySQL Server. It ensures that even if you shut down and restart your computer, the data remains safe in the database.”*

This is the power of a **Database Management System (DBMS)**.



✅ **Mentor’s Key Takeaways:**

1. **Server must be running** (MySQL80 service). If stopped, Workbench won’t connect.
2. **Workbench is only a GUI** — the real work happens in MySQL Server.
3. **SHOW DATABASES** → See what exists.
4. **CREATE DATABASE** → Make your own.
5. **USE db_name** → Select the working database.
6. **CREATE TABLE** → Define structure (columns, types).
7. **INSERT INTO** → Add data (rows).
8. **SELECT** → Retrieve data back.

Nice — let’s keep this in that same mentor-storytelling groove. Sit back like you’re in the lab with me and I’ll narrate the rest: why MySQL saves you from writing low-level code, how you bulk-insert and script data, the kinds of SQL commands you’ll use, and the real-world architecture where databases sit. Short scenes, practical bits, and small code examples you can paste in Workbench. 🎓



🎬 **Scene — The Hidden Work of Oracle’s Engineers**
Imagine a team of engineers in shirts and coffee cups (Oracle’s folks). They wrote the MySQL engine in C/C++ — internal data structures, file I/O, indexing, locking, crash recovery — all the low-level plumbing. You don’t need to re-invent that wheel. Instead, you learn *commands* (SQL) that tell that engine what to do. That’s **abstraction**: complex internals hidden, simple language exposed.

> Bottom line: you don’t write `fopen`/`fread`/`fwrite` — you write `INSERT`, `SELECT`, `CREATE TABLE`. MySQL handles persistence, concurrency, durability.
---

🎬 **Scene — Adding Many Records (the practical bit)**
You want to add several students/users. Instead of running a single `INSERT` 10 times, you can paste multiple `INSERT` commands or use a multi-row `INSERT`. Example:

```sql
-- single row (works)
INSERT INTO Students (ID, FirstName, LastName, Birth_Date, Email, Phone_Number)
VALUES (1, 'Pranav', 'Sharma', '2001-05-20', 'pranav@gmail.com', '9876543210');

-- multi-row (faster when inserting many)
INSERT INTO Students (ID, FirstName, Last_Name, Birth_Date, Email, Phone_Number)
VALUES
  (2, 'Sanika', 'Patil', '2002-03-05', 'sanika@gmail.com', '9876501234'),
  (3, 'Sarthak', 'Kumar', '2000-11-12', 'sarthak@gmail.com', '9876512345'),
  (4, 'Arun', 'Joshi', '1999-08-01', 'arun@gmail.com', '9876523456');
```

Or, paste many `INSERT` statements in one `.sql` file and run it in Workbench — that’s exactly what we do for sample data.
---

🎬 **Scene — Scripts & Reproducibility (your GitHub flow)**
You saw the **TfL e-commerce** repo: `create_db.sql`, `sample_data.sql` etc. That’s best practice:

1. `create_db.sql` → creates DB and tables (DDL).
2. `sample_data.sql` → inserts test/sample rows (DML).
3. Run both in Workbench (or via CLI: `mysql -u root -p < create_db.sql`).

This way any teammate can reproduce the entire database locally.



🎬 **Scene — DDL vs DML vs SQL (the short definitions)**

* **DDL (Data Definition Language)** — commands that define schema: `CREATE DATABASE`, `CREATE TABLE`, `ALTER TABLE`, `DROP TABLE`.
* **DML (Data Manipulation Language)** — commands that manipulate data: `INSERT`, `UPDATE`, `DELETE`.
* **SQL (Structured Query Language)** — the language that includes both DDL and DML (and DCL, TCL etc).

---

🎬 **Scene — A practical sample: users + products (e-commerce basics)**

```sql
CREATE DATABASE IF NOT EXISTS TFLE_Commerce;
USE TFLE_Commerce;

CREATE TABLE Users (
  UserID INT AUTO_INCREMENT PRIMARY KEY,
  UserName VARCHAR(50) NOT NULL,
  PasswordHash VARCHAR(255) NOT NULL,   -- store hashed passwords, never plain text
  Email VARCHAR(100),
  Address TEXT,
  CreatedAt DATETIME DEFAULT CURRENT_TIMESTAMP
);

CREATE TABLE Categories (
  CategoryID INT AUTO_INCREMENT PRIMARY KEY,
  Name VARCHAR(100)
);

CREATE TABLE Products (
  ProductID INT AUTO_INCREMENT PRIMARY KEY,
  Name VARCHAR(200),
  CategoryID INT,
  Price DECIMAL(10,2),
  Stock INT DEFAULT 0,
  FOREIGN KEY (CategoryID) REFERENCES Categories(CategoryID)
);
```

Notes: use `AUTO_INCREMENT` for surrogate keys; store password **hashes**; use `DECIMAL` for money.

---

🎬 **Scene — Querying only what you need**
Avoid `SELECT *` when you only need a few columns. Example:

```sql
SELECT FirstName, LastName FROM Students;
-- vs
SELECT * FROM Students;  -- all columns
```

Selecting specific columns reduces network/bandwidth and is a better habit.



🎬 **Scene — Relationships, constraints & performance**

* Use **primary key** + **foreign key** constraints to model relationships (orders → users, order_items → products).
* Add **indexes** on columns you search/sort often (e.g., `Email`, `ProductID`) to speed SELECTs.
* But don’t over-index — indexes slow down INSERT/UPDATE.



🎬 **Scene — How applications use the DB (the tech glue)**
Your DB is the backend engine. Languages/frameworks connect via drivers/ORMs:

* C/C++ → ODBC / native connectors
* .NET → ADO.NET / Entity Framework
* Java → JDBC / Hibernate
* Python → mysql-connector-python / SQLAlchemy
  These let your app run queries and fetch results into objects or data structures.



🎬 **Scene — Why data is the fuel**
I told the class: software without data is like a car without fuel. Apps exist because of data — customers, products, orders, logs. If you can’t store, retrieve, analyze data, an app has limited value. That’s why SQL skills + DB design matter.

---

🎬 **Final scene — Practice plan (do this now)**

1. Clone your `TfL e-commerce` repo.
2. Open `create_db.sql` in Workbench → run it.
3. Open `sample_data.sql` → run it (populate tables).
4. Run queries: `SELECT COUNT(*) FROM Products;`, `SELECT FirstName, LastName FROM Students;`
5. Modify schema: add a new column, insert a row, try `UPDATE` and `DELETE`.
6. Write 5 business questions and write SQL to answer them (e.g., top 5 products by sales).

---

### Quick checklist / reminders

* Use semicolons `;` to terminate SQL statements.
* Use `USE db_name;` to select the working DB.
* Don’t store plain passwords. Hash them.
* Use `.sql` scripts for reproducibility.
* Learn DDL → DML → Query optimization in that order.




## **Option 1: Ready-to-run SQL scripts**

✅ **create_db.sql**

```sql
-- create_db.sql
DROP DATABASE IF EXISTS tfl_ecommerce;
CREATE DATABASE tfl_ecommerce;
USE tfl_ecommerce;

-- Users table
CREATE TABLE users (
    user_id INT AUTO_INCREMENT PRIMARY KEY,
    full_name VARCHAR(100) NOT NULL,
    email VARCHAR(100) UNIQUE NOT NULL,
    password_hash VARCHAR(255) NOT NULL,
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);

-- Products table
CREATE TABLE products (
    product_id INT AUTO_INCREMENT PRIMARY KEY,
    name VARCHAR(100) NOT NULL,
    description TEXT,
    price DECIMAL(10,2) NOT NULL,
    stock INT DEFAULT 0,
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);

-- Orders table
CREATE TABLE orders (
    order_id INT AUTO_INCREMENT PRIMARY KEY,
    user_id INT NOT NULL,
    order_date TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    status ENUM('Pending','Shipped','Delivered','Cancelled') DEFAULT 'Pending',
    FOREIGN KEY (user_id) REFERENCES users(user_id)
);

-- Order items
CREATE TABLE order_items (
    order_item_id INT AUTO_INCREMENT PRIMARY KEY,
    order_id INT NOT NULL,
    product_id INT NOT NULL,
    quantity INT NOT NULL,
    price DECIMAL(10,2) NOT NULL,
    FOREIGN KEY (order_id) REFERENCES orders(order_id),
    FOREIGN KEY (product_id) REFERENCES products(product_id)
);

-- Payments
CREATE TABLE payments (
    payment_id INT AUTO_INCREMENT PRIMARY KEY,
    order_id INT NOT NULL,
    amount DECIMAL(10,2) NOT NULL,
    method ENUM('CreditCard','UPI','Wallet','COD') NOT NULL,
    payment_date TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    FOREIGN KEY (order_id) REFERENCES orders(order_id)
);
```

✅ **sample_data.sql**

```sql
USE tfl_ecommerce;

-- Users
INSERT INTO users (full_name, email, password_hash) VALUES
('Alice Johnson', 'alice@example.com', 'hash1'),
('Bob Smith', 'bob@example.com', 'hash2'),
('Charlie Brown', 'charlie@example.com', 'hash3');

-- Products
INSERT INTO products (name, description, price, stock) VALUES
('Laptop', '15 inch Core i7 Laptop', 75000.00, 10),
('Smartphone', '5G Android Smartphone', 30000.00, 20),
('Headphones', 'Noise Cancelling Headphones', 5000.00, 50);

-- Orders
INSERT INTO orders (user_id, status) VALUES
(1, 'Pending'),
(2, 'Shipped');

-- Order items
INSERT INTO order_items (order_id, product_id, quantity, price) VALUES
(1, 1, 1, 75000.00),
(1, 3, 2, 5000.00),
(2, 2, 1, 30000.00);

-- Payments
INSERT INTO payments (order_id, amount, method) VALUES
(1, 85000.00, 'CreditCard'),
(2, 30000.00, 'UPI');
```

Run order:

```bash
mysql -u root -p < create_db.sql
mysql -u root -p < sample_data.sql
```

---

## **Option 2: Simple Architecture Diagram**

```
+---------+        +----------------+         +------------------+
|  Client | <----> |  Backend App   | <-----> |  MySQL Server    |
| (Browser|        | (Java/.NET/Py) |         |  (with Workbench)|
+---------+        +----------------+         +------------------+
```

📌 Client (UI) → REST API → MySQL (data persisted).
Workbench is just for developers/admins to **see tables, run SQL queries, and manage DB**.

---

## **Option 3: Practice SQL Exercises**

1. Show all users.

   ```sql
   SELECT * FROM users;
   ```

2. Find products with stock less than 15.

   ```sql
   SELECT name, stock FROM products WHERE stock < 15;
   ```

3. List all orders with user’s full name.

   ```sql
   SELECT o.order_id, u.full_name, o.status 
   FROM orders o JOIN users u ON o.user_id = u.user_id;
   ```

4. Count how many orders each user has placed.

   ```sql
   SELECT u.full_name, COUNT(o.order_id) AS total_orders
   FROM users u LEFT JOIN orders o ON u.user_id=o.user_id
   GROUP BY u.full_name;
   ```

5. Find top 2 most expensive products.

   ```sql
   SELECT name, price FROM products ORDER BY price DESC LIMIT 2;
   ```

6. Show pending orders only.

   ```sql
   SELECT * FROM orders WHERE status='Pending';
   ```

7. Show all order items for order_id=1.

   ```sql
   SELECT p.name, oi.quantity, oi.price
   FROM order_items oi JOIN products p ON oi.product_id=p.product_id
   WHERE order_id=1;
   ```

8. Total sales amount for each user.

   ```sql
   SELECT u.full_name, SUM(p.amount) AS total_spent
   FROM payments p JOIN orders o ON p.order_id=o.order_id
   JOIN users u ON o.user_id=u.user_id
   GROUP BY u.full_name;
   ```

9. Update stock after purchase (reduce by 1 for product_id=2).

   ```sql
   UPDATE products SET stock=stock-1 WHERE product_id=2;
   ```

10. Delete cancelled orders.

```sql
DELETE FROM orders WHERE status='Cancelled';
```
 