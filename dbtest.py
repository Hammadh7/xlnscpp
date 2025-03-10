#compare ideal in python and C++
import xlns as xl
import os
xl.xlnssetF(7)

for z in range(1,1024):
   py = (xl.xlns(-1)+xl.xlnsB**(-z)).x
   # Use Windows path format with proper error handling
   try:
       cmd = f".\\db16.exe {str(-z)}"
       result = os.popen(cmd).read().strip()
       c = int(result) if result else 0
   except Exception as e:
       print(f"Error running db16: {e}")
       continue
   
   if (py-c) != 0:
       print(str(z)+" "+str(py-c), end=" ")
       print(py, end=" ")
       print(c)

