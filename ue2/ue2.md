###Betriebs- und Kommunikationssysteme | Zettel 2
Studenten: Evghenii Orenciuc, Jonathan Rex
Tutor: Abraham Söyler

####Aufgabe 1

######Begriffe

Interrupts:

    An interrupt is a hardware mechanism that enables CPU to detect
    that a device needs its attention.

    Interrupt becomes inefficient when devices keep on interrupting the CPU repeatedly.


Polling:

    Polling is a protocol that notifies CPU that a device needs its attention.
    It's asking the I/O device whether it needs CPU processing.

    Polling becomes inefficient when CPU rarely finds a device ready for service.

Source:
https://techdifferences.com/difference-between-interrupt-and-polling-in-os.html


||1	|2	|3	|4	|5	|6	|7	|8	|9	|10	|11	|12	|13	|14	|15	|16	|17 |
|--|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|
|I0	|R	|R	|R	|R													
I1	||	w|	w|	w|	w|	w|	w|	w|	w|	w|	w|	w|	w|	w|	R|	|
I2|	|	w|	w|	w|	w|	w|	w|	w|	w|	R|	R|	|	|	|	|	|
I3|	|	|	w|	w|	R|	R|	R|	|	|	|	|	|	|	|	|	|
I4|	|	|	|	|	w|	w|	w|	w|	w|	w|	w|	R|	R|	R|	|	|
I5|	|	|	|	|	|	w|	w|	R|	R|	|	|	|	|	|	|	|
I6|	|	|	|	|	|	|	w|	w|	w|	w|	w|	w|	w|	w|	w|	R



||1|   2|	3|	4|	5|	6|	7|	8|	9|	10|	11|	12|	13|	14|	15|	16|	17
|--|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|
I0|	R|	w|	w|	R|	w|	w|	w|	w|	w|	w|	w|	R|	R|	|	|	|
I1|	|	w|	w|	w|	w|	w|	w|	w|	w|	w|	w|	w|	w|	R|	|	|
I2|	|	R|	w|	w|	w|	w|	w|	R|	|	|	|	|	|	|	|	|
I3|	|	|	R|	R|	R|	|	|	|	|	|	|	|	|	|	|	|
I4|	|	|	|	|	w|	w|	w|	w|	R|	R|	R|	|	|	|	|	|
I5|	|	|	|	|	|	R|	R|	|	|	|	|	|	|	|	|	|
I6|	|	|	|	|	|	|	w|	w|	w|	w|	w|	w|	w|	w|	R|	|
