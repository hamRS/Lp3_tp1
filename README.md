# Merge sort using fork

## Compile mergeFork.c using  **-lm** for math lib

### When running  use

1. **./example <*number_processes*> <*comma separated array*>**
    * **Use case example:** ./mergeFork 7 5,4,8,9,3,1,4,7,8,9,5,4,8,7,9,6

### Considerations

* **The number of processes has to be odd**
  * so that sub-arrays have left and rigth childs
* **The number of processes has te be less than or equal the length of the array**
  * in that case is a complete merge sort, with one process for every sub-array until length of 1 is reached
