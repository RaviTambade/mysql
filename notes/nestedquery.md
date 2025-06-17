
##  *“The Tale of the Inner Hero — Understanding Nested SQL Queries”*

### 🎬 Once Upon a Query...

Let me take you into the world of **databases**, where every question we ask is called a **query**.

But sometimes, the question isn’t simple. It's *a question inside another question*.

Sounds confusing? Let’s step into a story...

### 🕵️‍♂️ Scene 1: The Detective and the Secret List

Imagine you are a detective.

You’re given a case:

> “Find all employees who earn **more than the average salary**.”

You could do this in two steps:

1. First, **calculate the average salary** of all employees.
2. Then, **find those who earn more than that**.

But what if I told you SQL lets you **ask both questions at once**, like a skilled detective who asks:

> “Hey database, give me all employees whose salary is **greater than (the average salary you calculate right now)**.”

Boom. That’s a **nested query** — also called a **subquery**.

### 🧠 What is a Nested Query?

A **nested query** is when you put a **query inside another query**.

Like this:

```sql
SELECT name, salary
FROM employees
WHERE salary > (
    SELECT AVG(salary)
    FROM employees
);
```

> 💡 The **inner query** calculates the average salary.
> The **outer query** uses that result to filter records.

### 🍱 Think of it like a Tiffin Box!

Imagine a lunchbox (SQL query) with smaller boxes inside (subqueries). You open the small one first (inner query), eat the food (result), and then move to the next one (outer query) with that flavor in mind.

SQL works the same way:

* The **inner query runs first**.
* The **outer query uses its result**.

### 🔍 Scene 2: The Top Performer

You now want to find the **employee with the highest salary**.

You can use:

```sql
SELECT name
FROM employees
WHERE salary = (
    SELECT MAX(salary)
    FROM employees
);
```

See the beauty?

You're telling SQL:

> “Find me the person whose salary **matches the maximum salary** in the company.”

### 🎯 Types of Nested Queries

There are **three types** of nested queries:

1. ✅ **Single Row Subqueries**
   Return only one value.
   Eg: `=`, `>`, `<` with `MAX()`, `AVG()`, etc.

2. 📋 **Multiple Row Subqueries**
   Return a list of values.
   Eg: `IN`, `ANY`, `ALL`

   ```sql
   SELECT name FROM employees
   WHERE department_id IN (
       SELECT id FROM departments WHERE location = 'Pune'
   );
   ```

3. 🧠 **Correlated Subqueries**
   These are *smart ones* — they **depend on the outer query**.

   Example:

   ```sql
   SELECT name
   FROM employees e1
   WHERE salary > (
       SELECT AVG(salary)
       FROM employees e2
       WHERE e1.department_id = e2.department_id
   );
   ```

   This finds employees who earn more than the **average in their department** — not overall.

   > Like comparing students in their own class, not the entire school.

### 💬 Mentor’s Note

> “You can always split a subquery into two simple queries first. But learning to nest them gives you the **power of real-world analytics**.”

Nested queries are used in:

* Finding **top-N performers**
* Matching **foreign keys dynamically**
* Performing **comparisons with live data**
* Creating **modular, readable SQL**

### 🧪 Try This Challenge:

🧩 *Find the names of employees who work in the same department as 'Saili'*

```sql
SELECT name
FROM employees
WHERE department_id = (
    SELECT department_id
    FROM employees
    WHERE name = 'Saili'
);
```
