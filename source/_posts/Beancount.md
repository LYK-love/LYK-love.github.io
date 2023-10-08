---
title: Beancount
tags: Beancount
catefories: Toolkit
date: 2023-10-07 19:29:03
---


Ref:

* Beancount [documentation](https://beancount.github.io/)
* [How to manage your finances with Beancount -- CoolByte](https://coolbyte.eu/2022/beancount-finances/)

<!--more-->

# Intro

* [Beancount](https://beancount.github.io/): A double-entry bookkeeping computer language that lets you define financial transaction records in a text file, read them in memory, generate a variety of reports from them, and provides a web interface.

  (Python > 3.5)

  ```
  sudo -H python3 -m pip install beancount
  ```

* [Fava](https://beancount.github.io/fava/) is a web interface for the double-entry bookkeeping software [Beancount](https://beancount.github.io/) 

  ```
  pip3 install fava
  fava ledger.beancount
  ```

# How Beancount works

The official Beancount [documentation](https://beancount.github.io/).

There are 5 types of accounts: `income`, `equities`, `liabilities`, `expenses` and `assets`. For details on what each account type represents it’s much better to consult the [related documentation](https://beancount.github.io/docs/beancount_language_syntax.html#accounts).

Now, in our ledger we will have to:

- Declare some options (such as the ledger name, the default currency, etc.)
- Open the accounts
- Create a baseline (usually using `equities`) for the current state of the assets
- Add transactions

# Brief Syntax Overview

A few notes and an ultra brief overview of the Beancount syntax:

- Currencies must be entirely in capital letters (allowing numbers and some special characters, like “_” or “-”). Currency symbols (such as $ or €) are not supported.
- Account names do not admit spaces (though you can use dashes), and must have at least two components, separated by colons. Each component of an account name must begin with a capital letter or number.
- Description strings must be quoted, like this: `"AMEX PMNT"`.
- Dates are only parsed in ISO8601 format, that is, YYYY-MM-DD.
- Tags must begin with “#”, and links with “^”.

For a complete description of the syntax, visit the [User’s Manual](https://beancount.github.io/docs/beancount_language_syntax.html).

# Validating your File

The purpose of Beancount is to produce reports from your input file (either on the console or serve via its web interface). However, there is a tool that you can use to simply load its contents and make some validation checks on it, to ensure that your input does not contain errors. Beancount can be quite strict; this is a tool that you use while you’re entering your data to ensure that your input file is legal. The tool is called “bean-check” and you invoke it like this:

```sh
bean-check /path/to/your/file.beancount
```

# Viewing the Web Interface

A convenient way to view reports is to bring up the “bean-web” tool on your input file. Try it:

```
bean-web /path/to/your/file.beancount
```



If you have Fava:

```sh
fava /path/to/your/file.beancount
```





# How to Organize your File

In this section we provide general guidelines for how to organize your file. This assumes you’ve read the [Language Syntax](https://beancount.github.io/docs/beancount_language_syntax.html) document.



### Preamble to your Input File

I recommend that you begin with just a single file[1](https://beancount.github.io/docs/getting_started_with_beancount.html#fn:1). My file has a header that tells Emacs what mode to open the file with, followed by some common options:

```
option "title" "XXX's Personal Ledger"
option "operating_currency" "USD"
option "operating_currency" "CNY"
```

## Sections & Declaring Accounts

I like to organize my input file in sections that correspond to each real-world account. Each section defines all the accounts related to this real-world account by using an Open directive. For example, this is a checking account:

```
2007-02-01 open Assets:US:BofA:Savings              USD
2007-02-01 open Income:US:BofA:Savings:Interest     USD
```

# De-duping

Finally, when I know I import just one side of these, I select the other account manually and I mark the posting I know will be imported later with a flag, which tells me I haven’t de-duped this transaction yet:

```
2014-06-10 * "AMEX EPAYMENT    ACH PMT"
  Liabilities:US:Amex:Platinum       923.24 USD
  ! Assets:CA:BofA:Checking
```

Later on, when I import the checking account’s transactions and go fishing for the other side of this payment, I will find this and get a good feeling that the world is operating as it should.

# Syntax

## Comments

The Beancount input file isn’t intended to contain only your directives: you can be liberal in placing comments and headers in it to organize your file. Any text on a line after the character “;” is ignored, text like this:

```
; I paid and left the taxi, forgot to take change, it was cold.
2015-01-01 * "Taxi home from concert in Brooklyn"
  Assets:Cash      -20 USD  ; inline comment
  Expenses:Taxi
```

## Accounts

Beancount accumulates commodities in accounts. The names of these accounts do not have to be declared before being used in the file, they are recognized as “accounts” by virtue of their syntax alone[1](https://beancount.github.io/docs/beancount_language_syntax.html#fn:1). An account name is a colon-separated list of capitalized words which begin with a letter, and whose first word must be one of five account types:

```
Assets Liabilities Equity Income Expenses
```

Each component of the account names begin with a capital letter or a number and are followed by letters, numbers or dash (-) characters. All other characters are disallowed.

Here are some realistic example account names:

```
Assets:US:BofA:Checking
Liabilities:CA:RBC:CreditCard
Equity:Retained-Earnings
Income:US:Acme:Salary
Expenses:Food:Groceries
```

The set of all names of accounts seen in an input file implicitly define a hierarchy of accounts (sometimes called a **chart-of-accounts**), similarly to how files are organized in a file system. For example, the following account names:

```
Assets:US:BofA:Checking
Assets:US:BofA:Savings
Assets:US:Vanguard:Cash
Assets:US:Vanguard:RGAGX
Assets:Receivables
```

implicitly declare a tree of accounts that looks like this:

```
`-- Assets
    |-- Receivables
    `-- US
        |-- BofA
        |   |-- Checking
        |   `-- Savings
        `-- Vanguard
            |-- Cash
            `-- RGAGX
```

We would say that “`Assets:US:BofA`” is the parent account of “`Assets:US:BofA:Checking`”, and that the latter is a child account of the former.

## Directives

### Transactions

Transactions are the most common type of directives that occur in a ledger. They are slightly different to the other ones, because they can be followed by a list of postings. Here is an example:

```
2014-05-05 txn "Cafe Mogador" "Lamb tagine with wine"
  Liabilities:CreditCard:CapitalOne         -37.45 USD
  Expenses:Restaurant
```

As for all the other directives, a transaction directive begins with a date in the *YYYY-MM-DD* format and is followed by the directive name, in this case, “`txn`”. However, because transactions are the *raison d’être* for our double-entry system and as such are by far the most common type of directive that should appear in a Beancount input file, we make a special case and allow the user to elide the “txn” keyword and just use a flag instead of it:

```
2014-05-05 * "Cafe Mogador" "Lamb tagine with wine"
  Liabilities:CreditCard:CapitalOne         -37.45 USD
  Expenses:Restaurant
```

A flag is used to indicate the status of a transaction, and the particular meaning of the flag is yours to define. We recommend using the following interpretation for them:

- *: Completed transaction, known amounts, “this looks correct.”
- !: Incomplete transaction, needs confirmation or revision, “this looks incorrect.”

In the case of the first example using “txn” to leave the transaction unflagged, the default flag (“*”) will be set on the transaction object. (I nearly always use the “*” variant and never the keyword one, it is mainly there for consistency with all the other directive formats.)

You can also attach flags to the postings themselves, if you want to flag one of the transaction’s legs in particular:

```
2014-05-05 * "Transfer from Savings account"
  Assets:MyBank:Checking            -400.00 USD
  ! Assets:MyBank:Savings
```

This is useful in the intermediate stage of de-duping transactions (see [Getting Started](https://beancount.github.io/docs/getting_started_with_beancount.html) document for more details).

The general format of a Transaction directive is:

```
YYYY-MM-DD [txn|Flag] [[Payee] Narration] [Flag] Account Amount [{Cost}] [@ Price] [Flag] Account Amount [{Cost}] [@ Price] ...
```

The lines that follow the first line are for “Postings.” You can attach as many postings as you want to a transaction. For example, a salary entry might look like this:

```
2014-03-19 * "Acme Corp" "Bi-monthly salary payment"
  Assets:MyBank:Checking             3062.68 USD     ; Direct deposit
  Income:AcmeCorp:Salary            -4615.38 USD     ; Gross salary
  Expenses:Taxes:TY2014:Federal       920.53 USD     ; Federal taxes
  Expenses:Taxes:TY2014:SocSec        286.15 USD     ; Social security
  Expenses:Taxes:TY2014:Medicare       66.92 USD     ; Medicare
  Expenses:Taxes:TY2014:StateNY       277.90 USD     ; New York taxes
  Expenses:Taxes:TY2014:SDI             1.20 USD     ; Disability insurance
```

The Amount in “Postings” can also be an arithmetic expression using `( ) * / - +` . For example,

```
2014-10-05 * "Costco" "Shopping for birthday"
  Liabilities:CreditCard:CapitalOne         -45.00          USD
  Assets:AccountsReceivable:John            ((40.00/3) + 5) USD
  Assets:AccountsReceivable:Michael         40.00/3         USD
  Expenses:Shopping
```

The crucial and only constraint on postings is that the sum of their balance amounts must be zero. This is explained in full detail below.

### Payee & Narration

A transaction may have an optional “payee” and/or a “narration.” In the first example above, the payee is “Cafe Mogador” and the narration is “Lamb tagine with wine”.



If you place a single string on a transaction line, it becomes its narration:

```
2014-05-05 * "Lamb tagine with wine"
   …
```

If you want to set just a payee, put an empty narration string:

```
2014-05-05 * "Cafe Mogador" ""
   …
```
