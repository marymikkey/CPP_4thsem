# Install SQLite
```
sudo apt install sqlite3 libsqlite3-dev 
```

# Build
```
mkdir -p ~/build/user-mgmt
cd ~/build/user-mgmt
cmake ~/src/user-mgmt
make
```

# Run
```
user-mgmt user create vanya "Ivan Ivanov"
user-mgmt user create tony "Antony Simpson"
user-mgmt group create botanics
user-mgmt group add botanics vanya
user-mgmt group add botanics tony
user-mgmt group get-all
user-mgmt user get-all
```
