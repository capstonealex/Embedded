First successful PDO mapping.
Mapped with:
1. Control word 
2. Status Word
3. Motor position
4. Motor velocity
5. Target position
6. Target velocity
Sub index 0, hold the number of motors (4 for the X2).
Sub index 1, holds the corresponding value (status word, position etc) for node 1.
Sub index 2 for node 2 and so on.

Torque actual value is mapped to status word in this version.