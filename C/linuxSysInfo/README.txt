Part B:

go to directory with partb.c
	gcc partb.c -o partB
	partB | partB -s [Throws Exception]| partB -s -l [Throws Exception]
----------------------------------------------------------------------------------------

Part C:

go to directory with partc.c
	gcc partc.c -o partC
	partC | partC [-s] (Throws Exception)| partC [-s] [-l int dur] (Throws Exception)

-----------------------------------------------------------------------------------------

Part D:

go to directory with partd.c
	gcc partd.c -o partD
	partD | partD [-s] | partD -s [-l int dur] 

-----------------------------------------------------------------------------------------

Only known error: Total process count comes out as Segmentation Error.