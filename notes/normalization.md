

## Understanding Entities, Tables, and Normalization**



👋 *Welcome students!* Today, I’ll take you into the world of **Data Modeling**. But instead of throwing dry definitions at you, let me walk you through this *as if you are building your own mini digital world.*



### 🌸 Imagine a Flower Shop

You are the proud owner of a beautiful online flower shop. You sell **products** like *Roses*, *Lotus*, *Lily*, and *Jasmine*. And guess what? These flowers are not just pretty—they’re going to teach us *Database Design*!



### 🔷 **What is an Entity?**

Think of an **entity** as a *real-world object* that has identity and meaning in our system.

🟡 Examples:

* 🌹 Product (Like Rose or Jasmine)
* 👤 Customer
* 🎓 College
* 🏢 Department

Each of these **entities** has some **characteristics**, right? That’s what we call **attributes**.


### 🧩 **Defining Entities through Attributes**

Let’s define our **Product** entity:

| Attribute   | Example          |
| ----------- | ---------------- |
| ID          | 101              |
| Title       | “Valentine Rose” |
| Description | “Fresh red rose” |
| Price       | ₹75              |

In the same way, a **Customer** could have:

* ID: 501
* First Name: Ravi
* Last Name: Tambade
* Email: [ravi@example.com](mailto:ravi@example.com)

And a **College** could have:

* College ID
* Name
* Location

That’s how we build **entities** using **attributes**.

### 🗃️ **What is a Table in SQL?**

A **table** is just a structured collection of entities of the same type.

So a **Product Table** will hold *many rows*, each row representing a different product.

📦 Table = Collection of records = Collection of entities

Each **row** is like one flower in your store. It has:

* A unique ID (like barcode),
* A name,
* A price.

### 🔑 **Primary Key and Foreign Key**

🔹 A **Primary Key** uniquely identifies each record in a table.
You can’t have duplicates here—it’s like your Aadhaar card number.

🔹 A **Foreign Key** connects one table to another.
It helps build **relationships**. Think of it like saying:

* “This review is for that product.”

🧠 **Example:**

* **Product Table** has `ProductID` as a primary key.
* **Ratings Table** has `ProductID` as a foreign key (to know which product the rating is for).

### 🧱 **Master Table vs Transaction Table**

* 🧭 **Master Table**: Stores permanent core info.
  ➤ Example: Product, Customer, College

* 📄 **Transaction Table**: Stores temporary or action-based info.
  ➤ Example: Rating, Likes, Comments

Each time someone likes a flower, we store:

* ProductID → (From Product Table)
* LikeID → Unique for each like
* Timestamp → When it happened

### 🔃 **Normalization – Divide & Rule**

🪄 **Normalization** means splitting your data smartly across tables to:

* Avoid duplication
* Maintain consistency
* Keep your data clean

Let’s say, you had a single giant table with repeated product names again and again every time a customer liked it. What if you changed the price of a flower? You’d have to update it **everywhere**.

Instead, keep:

* Product info in one table
* Likes, Ratings, Comments in separate tables
* Connect them using keys

This way, no repetition. One change updates everything.

🧠 **That’s the power of Normalization!**

### 🔁 **Denormalization – The Trade-off**

Sometimes, to **speed up reading**, we join two tables and store the result temporarily.

This is **denormalization**. It's like packing all info in one place to read fast—but be careful, it can increase data redundancy.

### ⚡ **Transient Table – Temporary Guests**

A **transient table** is like a temporary notepad on your desk:

* It stores data *only for a short time*
* Mostly used for **sessions**, **logs**, or **temporary selections**
* Once work is done, *poof!* it's gone

### 🧵 Stitching It All Together

📌 You have:

* **Entities**: Product, Customer, College, Department
* **Attributes**: ID, Name, Price, etc.
* **Tables**: Product table, Likes table, Ratings table
* **Keys**: Primary Key (unique), Foreign Key (reference)
* **Normalization**: To avoid repetition
* **Denormalization**: For performance boost
* **Transient Tables**: Temporary storage


## 🧠 **Understanding Master, Detail, and Transient Tables**


### 🔹 **Master Tables: The Foundation**

These are the independent tables—like the *roots of a tree*.
They hold **core entity data** like:

* `Employees`
* `Subjects`

> “Master table has a **Primary Key**, but no **Foreign Key**. It doesn't depend on others—just like a teacher's identity is not dependent on which class they teach.”

---

### 🔸 **Detail Tables: The Branches**

Detail tables store information **related to master tables**.
They contain:

* One **Primary Key**
* One or more **Foreign Keys**

Examples:

* `Interview`
* `Result`
* `EmployeePerformance`

> “Imagine every *Result* belongs to a particular *Employee* and a *Subject*. Detail tables connect like **branches to roots**.”

---

### 🔁 **Transient (Transaction) Tables: The Connectors**

Used to **break many-to-many** relationships.
They **connect two or more master/detail tables**.

Example:

* `OrderItems` connects `Orders` and `Products`
* `CandidateAnswers` connects `Candidate` and `Questions`

Structure:

* Only **Foreign Keys**
* No independent meaning—acts like a **bridge**

> “You can think of a transient table like a *train junction* that connects multiple tracks. No passengers live there—it only facilitates travel (data linking).”

---

### 🌼 **Real-World Analogy: Flower and Seed**

> “One flower can come from many seeds, and one seed can give many flowers.
> This is like **many-to-many** relationship—broken using a **transient table**.”

---

### 🧮 **Why Use Transient Tables?**

1. To **normalize data** (remove redundancy)
2. To **track relationships** like product purchases, test answers
3. To support **accurate data analysis**

---

### ✅ **In the TFL Assessment DB**

You taught how:

* `Employees` and `Subjects` = Master
* `Interview`, `Result` = Detail
* `CandidateAnswers` = Transient


##  The Tale of the Two Warehouse Managers – **A Story of Data Nagar**

Let me take you to a land called **Data Nagar**, where two wise warehouse managers once ruled the world of data:

* 🧑‍💼 **Mr. Norm** – The Master of Clean Records
* 🧔‍♂️ **Mr. Denorm** – The King of Speed and Simplicity

### 📦 Scene 1: Mr. Norm – The Perfectionist of Normalization

Mr. Norm’s warehouse was like a **library** — clean, well-structured, no confusion.
He followed one golden rule:

> “Don’t repeat yourself.”

Every item had a **unique spot**:

* 📁 Products Section
* 📁 Suppliers Section
* 📁 Customers Section

He **linked data using IDs** — so if a product belonged to a supplier, he stored the `SupplierID` only.

🔍 If a customer asked, “Who supplied this product?”, he’d travel through 3–4 sections, **look up relationships**, and give a perfect, verified answer.

### 📘 What is **Normalization**?

**Normalization** is the process of **organizing data** to:

* Reduce redundancy ✅
* Maintain consistency 🧹
* Improve data integrity 🔒

It divides large tables into **smaller, related ones**, linked by **Primary and Foreign Keys**.


### 🎯 Goals of Normalization

1. **Avoid duplication** of data
2. **Update in one place**
3. Prevent **anomalies** (like missing or inconsistent data)
4. Ensure **logical grouping** of information


### 🔢 Understanding Normal Forms (Simplified Table)

| Form | Rule Description                                    |
| ---- | --------------------------------------------------- |
| 1NF  | No repeating groups – Atomic values only            |
| 2NF  | 1NF + Full dependency on Primary Key                |
| 3NF  | 2NF + No indirect dependencies (transitive)         |
| BCNF | Even stricter: every determinant is a candidate key |


### 💡 Before Normalization

```plaintext
OrderID | CustomerName | ProductName | SupplierName
---------------------------------------------------
101     | Alice        | Pen         | ABC Traders
102     | Alice        | Notebook    | XYZ Suppliers
103     | Bob          | Pen         | ABC Traders
```

* 😬 Customer and supplier names are repeated
* Updates become painful!

### ✅ After Normalization

Break into **4 related tables**:

#### 1. Customers

| CustomerID | CustomerName |
| ---------- | ------------ |
| 1          | Alice        |
| 2          | Bob          |

#### 2. Suppliers

| SupplierID | SupplierName  |
| ---------- | ------------- |
| 1          | ABC Traders   |
| 2          | XYZ Suppliers |

#### 3. Products

| ProductID | ProductName | SupplierID |
| --------- | ----------- | ---------- |
| 1         | Pen         | 1          |
| 2         | Notebook    | 2          |

#### 4. Orders

| OrderID | CustomerID | ProductID |
| ------- | ---------- | --------- |
| 101     | 1          | 1         |
| 102     | 1          | 2         |
| 103     | 2          | 1         |

✔️ No duplication
✔️ Data consistency
✔️ Clean joins between entities

### 📉 Limitations of Normalization

* ❌ More **joins** (slower for complex queries)
* ❌ Slightly **harder schema design**
* ❌ May not be suitable for **analytics/reporting**


### 🏗️ Scene 2: Mr. Denorm – The Speed King

Mr. Denorm had a different mantra:

> “Speed matters more than structure.”

He merged **everything into one big table**, so if anyone asked:

> "Who sold this pen to Bob?"
> He'd answer **immediately**, no lookup needed!

Yes, the data had **duplication**, but it was **super fast to read**!


### 📕 What is **Denormalization**?

Denormalization is the process of **merging normalized tables**:

* **Reduces joins**
* **Increases query speed**
* **Adds redundancy** on purpose!


### 🔁 Why Denormalize?

* ⚡ High-speed dashboards
* 📊 Reporting/Analytics systems
* 🧠 Cache-heavy or read-heavy apps
* 📉 Simplify complex joins


### 🧾 Denormalized Example

```plaintext
OrderID | CustomerName | ProductName | SupplierName
----------------------------------------------------
101     | Alice        | Pen         | ABC Traders
102     | Alice        | Notebook    | XYZ Suppliers
103     | Bob          | Pen         | ABC Traders
```

✔️ Fast to read
❌ Hard to maintain if supplier name changes


### ⚖️ Comparison Table

| Feature           | Normalization           | Denormalization                   |
| ----------------- | ----------------------- | --------------------------------- |
| Redundancy        | Eliminated              | Introduced                        |
| Data Integrity    | High                    | Needs strict control              |
| Query Performance | Slower (more joins)     | Faster (fewer joins)              |
| Storage           | Efficient               | Requires more space               |
| Use Case          | OLTP systems (ERP, CRM) | OLAP systems (BI, Reports, Cache) |


### 🧠 Mentor’s Summary

> “A normalized system is like a well-maintained library — efficient, clean, and rule-driven.
> A denormalized system is like a public reading lounge — quick access, but messy if not managed.”


### 🔍 When to Use What?

| Scenario                             | Recommended Approach       |
| ------------------------------------ | -------------------------- |
| Banking, Transactional Apps          | ✅ Normalization            |
| Real-time Dashboards, BI tools       | ✅ Denormalization          |
| Forms and Data Capture               | ✅ Normalization            |
| Inventory Monitoring with Speed Need | 🔁 Partial Denormalization |

### 🧑‍🏫 Final Mentor Thought

> As a software engineer, always ask:
> **“Is my system read-heavy or write-heavy?”**
> Use **Normalization** for accuracy and structure.
> Use **Denormalization** *only when performance truly demands it*.
> Choose wisely. Like a mentor. Like a pro. 💡


### 🧪 **Assignments**

* **Draw an ER Diagram** showing master-detail-transient relationships.
* **Write SQL Queries** for business requirements using correct joins.
* Explain one real-world example (e.g., e-commerce or ticket booking) with all 3 table types.


### 💬 Mentor’s Final Words

"Just like we organize shelves in a shop, we organize data in a database. If the arrangement is smart, finding and updating things becomes super easy. That’s what makes a real engineer — someone who thinks *before building*, someone who designs for *scale and clarity*.”

> — *Mentor Ravi Tambade*
 