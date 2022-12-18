# Oasis Pro
# COMP 3004 Project - Fall 2022

| Deliverable     | Use cases 	| Use case diagrams 	| Traceability matrix 	| Class Diagrams 	| Sequence diagrams 	| Development 	| Testing 	|
|----------------	|-----------	|-------------------	|---------------------	|----------------	|-------------------	|-------------	|---------	|
| Ian Martin     	| X         	|        X          	|          X           	|                	|                   	| X           	|         	|
| Kris Giang     	|           	|                   	|                     	|                	| X                 	| X           	|         	|
| Mohamed Hamail 	|   X        	|          X         	| X                   	| X              	|                   	| X           	|         	|
| Carson Fischl  	|           	|                   	|                     	|                	|                   	| X           	|     X    	|

File organization:

```
OasisPro
├── 2048
├── backButton.svg
├── battery.cpp
├── battery.h
├── cesmc.cpp
├── cesmc.h
├── connection.cpp
├── connection.h
├── db.cpp
├── db.h
├── Documentation (class diagrams, traceability matrix)
│   ├── class diagram.png
│   ├── comp3004_finalproject_traceability_matrix.docx
│   ├── comp3004_finalproject_traceability_matrix.pdf
│   ├── comp3004_finalproject_usecases.docx
│   ├── OasisPro_UseCaseDiagram.png
│   └── Use_Cases_features_4-5.docx
├── downButton.svg
├── frequency.cpp
├── frequency.h
├── img.qrc
├── intensity.cpp
├── intensity.h
├── main.cpp
├── mainwindow.cpp
├── mainwindow.h
├── mainwindow.ui
├── Makefile
├── menu.cpp
├── menu.h
├── moc_mainwindow.cpp
├── moc_predefs.h
├── moc_therapy.cpp
├── oasis.db
├── OasisPro
├── OasisPro.pro
├── OasisPro.pro.user
├── okButton.svg
├── powerButton.svg
├── qrc_img.cpp
├── README.md
├── record.cpp
├── record.h
├── redSquare.png
├── SequenceDiags (sequence diagrams)
│   ├── UC10.png
│   ├── UC10.txt
│   ├── UC12.png
│   ├── UC12.txt
│   ├── UC13.png
│   ├── UC13.txt
│   ├── UC14.png
│   ├── UC14.txt
│   ├── UC1.png
│   ├── UC1.txt
│   ├── UC2.png
│   ├── UC2.txt
│   ├── UC3.png
│   ├── UC3.txt
│   ├── UC6.png
│   ├── UC6.txt
│   ├── UC8.png
│   ├── UC8.txt
│   ├── UC9.png
│   └── UC9.txt
├── session.cpp
├── session.h
├── target_wrapper.sh
├── therapy.cpp
├── therapy.h
├── ui_mainwindow.h
├── upButton.svg
├── user.cpp
└── user.h
```

Sequence Diagrams are in the SequenceDiags folder, class diagrams and traceability matrix are in Documentation. Headers and source files will appear in their respective folders in Qt Creator.

Tested Scenarios:

- Power on (buttons illuminate, LED turns on)
- Select a session type (20 min, 45 min, or user designated)
- Select a group (alpha, beta, gamma, theta frequencies)
- Soft off (intensity gradually increases/decreases)
- Connection test (clips must be connected/checkbox)
- History (loads from DB)
- Clear history (history can be cleared)
