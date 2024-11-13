## In SQL, pattern matching is powerful and allows for flexible querying with wildcards, operators, and regular expressions. Here’s a breakdown of pattern-matching possibilities:

### **1. LIKE and ILIKE**

The `LIKE` and `ILIKE` operators allow simple pattern matching with two main wildcards:

- **`%`**: Matches any sequence of characters (including an empty sequence).
- **`_`**: Matches exactly one character.

#### Examples:

```sql
-- Using `%` wildcard
SELECT * FROM employees WHERE name LIKE 'A%';
-- Matches any name that starts with "A" (e.g., "Alice", "Andrew").

-- Using `_` wildcard
SELECT * FROM products WHERE code LIKE 'A_B';
-- Matches codes like "A1B", "A2B" but not "AB" or "A12B".
```

#### Case-Insensitive Match

The `ILIKE` operator works similarly but is case-insensitive.

```sql
SELECT * FROM books WHERE title ILIKE '%harry%';
-- Finds any title containing "harry" in any case (e.g., "Harry Potter", "The World of Harry").
```

### **2. SIMILAR TO**

The `SIMILAR TO` operator uses SQL’s own simplified version of regular expressions. It’s often used to match patterns with more flexibility than `LIKE`, combining `%` and `_` with regular expression syntax.

#### Examples:

```sql
SELECT * FROM movies WHERE title SIMILAR TO '(Star|Galaxy)%';
-- Matches titles starting with either "Star" or "Galaxy".

SELECT * FROM students WHERE id SIMILAR TO '[A-Z]{2}[0-9]{4}';
-- Matches an ID that starts with two uppercase letters followed by four digits (e.g., "AB1234").
```

### **3. Regular Expressions (POSIX Regular Expressions)**

PostgreSQL and some other databases support POSIX regular expressions, which allow more complex pattern matching using operators such as `~` (case-sensitive) and `~*` (case-insensitive).

#### Basic POSIX Syntax:

- **`^`**: Matches the beginning of a string.
- **`$`**: Matches the end of a string.
- **`.`**: Matches any single character.
- **`[...]`**: Matches any single character within the brackets.
- **`|`**: Alternation (logical OR).
- **`*`, `+`, `?`**: Quantifiers (e.g., zero or more, one or more, zero or one).
- **`{}`**: Specify exact quantity or range.

#### Examples:

```sql
-- Case-sensitive regular expression
SELECT * FROM contacts WHERE email ~ '^info@';
-- Finds emails that start with "info@".

-- Case-insensitive regular expression
SELECT * FROM contacts WHERE email ~* 'gmail\.com$';
-- Finds emails ending with "gmail.com" in any case.

-- Using character ranges and quantifiers
SELECT * FROM orders WHERE order_code ~ '^[A-Z]{2}[0-9]{3}$';
-- Matches order codes with two uppercase letters followed by three digits (e.g., "AB123").
```

### **4. Special Character Classes in POSIX Regex**

POSIX regular expressions also offer special character classes for shorthand matching:

- **`\d`**: Matches any digit (equivalent to `[0-9]`).
- **`\D`**: Matches any non-digit.
- **`\w`**: Matches any word character (alphanumeric and underscore).
- **`\W`**: Matches any non-word character.
- **`\s`**: Matches any whitespace character.
- **`\S`**: Matches any non-whitespace character.

#### Examples:

```sql
SELECT * FROM users WHERE username ~ '^\w+$';
-- Matches usernames with only word characters (letters, numbers, underscores).

SELECT * FROM texts WHERE content ~ '\d{3}-\d{2}-\d{4}';
-- Finds content matching the pattern of a US Social Security number (e.g., "123-45-6789").
```

### **5. ESCAPE Clause in LIKE**

If you need to match literal `%` or `_` characters in a `LIKE` pattern, use an escape character.

#### Examples:

```sql
SELECT * FROM files WHERE name LIKE 'File#_%' ESCAPE '#';
-- Matches names starting with "File_" where `_` is a literal character, not a wildcard.

SELECT * FROM paths WHERE path LIKE '%//%' ESCAPE '/';
-- Finds paths containing literal "//".
```

### **6. Pattern Matching with ARRAY_CONTAINS**

Some SQL databases support array functions that can search within arrays directly. PostgreSQL allows you to use pattern matching within array elements.

#### Example:

```sql
SELECT * FROM teams WHERE '{Team A, Team B, Team C}'::text[] @> ARRAY['Team B'];
-- Checks if "Team B" is in the array (useful in JSON and array fields).
```

### **Summary of Pattern Matching Operators**

- **`%`**: Zero or more characters.
- **`_`**: Exactly one character.
- **`^`**: Start of string (regex only).
- **`$`**: End of string (regex only).
- **`.`**: Any single character (regex only).
- **`[...]`**: Any character in the set (regex only).
- **`\d`, `\w`, `\s`**: Character classes (regex only).
- **`|`**: OR (regex only).

These operators allow SQL queries to locate and filter records based on flexible patterns, whether through simple wildcard matches or advanced regex criteria.
