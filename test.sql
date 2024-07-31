

--employees table

-- Create a temporary table to store fetched rows
CREATE TEMPORARY TABLE temp_employees (
    id INT,
    name VARCHAR(50),
    salary DECIMAL(10, 2)
);

-- Declare a cursor for selecting employees in descending order
DECLARE emp_cursor CURSOR FOR 
    SELECT id, name, salary FROM employees ORDER BY id DESC;

-- Open the cursor
OPEN emp_cursor;

-- Fetch rows into the temporary table
FETCH emp_cursor INTO temp_employees;

-- Loop through the temporary table to navigate backward
REPEAT
    -- Process the fetched row
    -- For example, print the data
    SELECT id, name, salary FROM temp_employees;
    
    -- Fetch the previous row
    FETCH emp_cursor INTO temp_employees;
UNTIL (SQLSTATE = '02000') END REPEAT;

-- Close the cursor
CLOSE emp_cursor;

-- Drop the temporary table
DROP TEMPORARY TABLE temp_employees;
