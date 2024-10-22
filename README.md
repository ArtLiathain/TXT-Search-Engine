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
