# BakeryPOS
A Point Of Sale System for a Bakery made using PySide6.

## Screenshots
![products page](./readme-assets/product.png)

## How to run

### Prerequisites
1. [Python](https://www.python.org/)
2. [pip](https://pypi.org/project/pip/)
3. [MySql Server](https://www.mysql.com/)

### Clone Repo
```bash
git clone https://github.com/kazurem/BakeryPOS

# move into the cloned project
cd BakeryPOS

# Checkout to the python branch of BakeryPOS
git checkout bakepy
```

### Virtual Environment
```bash
python -m venv .venv

# linux
source .venv/bin/activate

#windows
.\.venv\Scripts\activate.bat
```

### Package Installation
The following command will install all the necessary packages.
```bash
pip install -r requirements.txt
```

### Database 
You need to have [MySql](https://www.mysql.com/) installed on your system too. After that, you'll need to create a user and set their password. Name the user **test** and set it's password to be **1234**. Once this has been done, you have to create a database using the _bakerydb.sql_ file. Name the database **bakerydb**.
> [!WARNING] 
> Username **test** and password **1234** are only a temporary solution, for the purposes of development.

### Build and Run
```bash
# move into the source directory
cd src

# run the project
python main.py
```
