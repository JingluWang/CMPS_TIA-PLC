# CMPS_TIA-PLC

### file location
C:\PLC for CMPS\2023_New_Testing\Full_CMPS_3Boxeswork\Full_CMPS_3Boxeswork \
-> folder: CMPS_PLC \[CPU 1212C AC/DC/Rly\] 

### Editing
1. Program blocks
 - Main \[OB1\]
![main](https://github.com/JingluWang/CMPS_TIA-PLC/assets/107279970/dbdb571e-4975-40a0-8d72-da22e7a8d3a7)


 - Block_2 \[FB1\] (Full_CMPS_3Boxeswork.txt)
![Block_2](https://github.com/JingluWang/CMPS_TIA-PLC/assets/107279970/4053b574-3d78-4488-8d24-cfa11e378b8a)


 - Block_2_DB \[DB1\]
![Block_2_DB](https://github.com/JingluWang/CMPS_TIA-PLC/assets/107279970/7339610d-c68c-49b0-b289-09f27263c7d2)


2. PLC tags
 - Default tag table
![Default_tag_table](https://github.com/JingluWang/CMPS_TIA-PLC/assets/107279970/83f4842a-2364-4abd-9398-62268cd722f2)




### Running
> - Compile (Right click on any modified block: only changed or all)
> - Download to device
> - Go Online
> - Monitor all (Watch table_2)

![Watch_table_2](https://github.com/JingluWang/CMPS_TIA-PLC/assets/107279970/5b580182-23ae-4a74-80e1-140d45b0f362)



## Calibration for Cold Mass Position System (CMPS)
Example: DS_03up

|                               | on prototype | \[0\] (x) | \[1\] (z) | \[2\] (y) | 
|   ---                         | ---          | ---       | ---       | ---       |
| DS_03up - change in \[0\] (x) | d_Reco       | -26347    | -483      | 743       |
|                               | d_Truth      | 25        | 0         | 0         |

|                               | on prototype | \[0\] (x) | \[1\] (z) | \[2\] (y) | 
|   ---                         | ---          | ---       | ---       | ---       |
| DS_03up - change in \[1\] (z) | d_Reco       | -358      | 30604     | 250       |
|                               | d_Truth      | 0         | 30        | 0         |

|                               | on prototype | \[0\] (x) | \[1\] (z) | \[2\] (y) | 
|   ---                         | ---          | ---       | ---       | ---       |
| DS_03up - change in \[2\] (y) | d_Reco       | -428      | 308       | -19238    |
|                               | d_Truth      | 0         | 0         | 20        |
