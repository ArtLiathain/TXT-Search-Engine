# TXT-Search-Engine

## Getting the books (Ethically)
```python
pip install -r requirements.txt
python3 downloadBooks.py 
```

## Building the project
Make sure the books are in a folder called archive at root of project
```
cmake --preset default;
cmake --build --preset default;
cd build
make
cd src/
./my_executable

OR

source runproject.sh
```

## Adding files to the build
```
add_executable(<Name of exe> <Name of file>)

```

## Testing the project
```
source testproject.sh
```

# Running the Project

Once built, the project can be run from build/src with:
```
./my_executable
```

The following options can be flagged with this command:

| Command          |Parameters                       | Description                                              |
|------------------|---------------------------------|----------------------------------------------------------|
| `-search`        |word*, operators {OR, NOT, AND}  | Search for books containing (or excluding) these words.  |
| `-autocomplete`  |prefix                           | Returns all words starting with the given prefix.        |
| `-addBook`       |path                             | Adds a book at the given path to the index.              |
| `-help`          |                                 | Displays all commands with descriptions.                 |
| `-forceSerialise`|                                 | Deserialises the index and autocomplete.                 |
| `-exit`          |                                 | Terminates the program.                                  |

After completion, the program will prompt another input
simply enter a new command (excluding "./my_executable")