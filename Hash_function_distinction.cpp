#include <iostream>
#include <set>
#include <ctime>
#include "md5.h"

#pragma warning(disable:4996)

#define LOWER_NUMBER 0x00000001		// Max number of random Numer ( 32 bit )
#define UPPER_NUMBER 0xFFFFFFFF		// Min number of random Number ( 32 bit )

#define MAX_DEPTH 50		// Number for depth set range

unsigned int hash(unsigned int num, unsigned int input, unsigned maxVal) { 
	
	/*	num: Hash Number
	*	input : Hash Key
	*	maxVal: Maximum output value
	*/

	// prime[30] are real primes. 1024 added later
	unsigned int prime[512 + 512] = {
		1500450271, 3267000013, 4093082899, 3628273133, 2860486313,
		256203221, 236887699, 217645199, 198491329, 179424691,
		160481219, 141650963, 122949829, 104395303, 86028157,
		67867979, 49979693, 32452867, 15485867, 198491317,
		999593627, 139054403, 792699101, 785734517, 273081631,
		714723547, 308218681, 653056661, 727112891, 422064359,
		984380991, 1164361327, 1813816658, 962540129, 1806629947,
		1620991093, 1968805576, 1813559041, 1099154204, 1438747492,
		1250455716, 1646065816, 1792609100, 1064355847, 1170052850,
		1150747808, 1287102234, 1903331369, 1401245412, 1929147095,
		1153516860, 1291469084, 1764096337, 1800205248, 1399931720,
		1021607475, 1659002161, 1515319074, 1851650106, 1509459784,
		1244889634, 1407136391, 980997873, 925210423, 1141906151,
		1930571710, 1850370226, 1439113824, 1730576356, 1653754713,
		1547091875, 1105276201, 975157666, 1288780592, 1690071377,
		1449308794, 1507793745, 1951036636, 1353937195, 1768168000,
		1203858753, 1942203453, 1401815813, 1617444843, 1608427368,
		1720508917, 1972911510, 1822099695, 927349728, 951976426,
		1714953465, 1863551814, 1648652646, 1601999304, 908928304, 1158824940, 1654541788, 959770493, 970036380, 1010949474, 1037177031, 1440718779, 1398417031, 1861617197, 995737042, 1732062329, 1695868315, 1215223636, 1256699721, 1494848371, 1806208616, 1897122533, 1386834078, 1368048805, 1079509473, 1656210032, 1703215336, 1496297684, 1128286175, 1691786634, 1633500511, 1802659845, 1838555549, 1893228619, 1967932386, 1858455556, 1273637947, 1045162448, 1340509553, 1424472798, 1617302331, 925743803, 1971085491, 1663042919, 1829688071, 1411435438, 1045814385, 1652598197, 1711344489, 1622406100, 1022759449, 941900195, 1270211089, 1738596184, 1281044540, 1701913936, 1832842514, 1191712235, 1178254608, 1884705181, 1384701285, 1824002370, 1632035055, 1938627250, 1318666597, 979821462,
		929710294, 1457149562, 969897810, 1374940707, 1946839271, 1867127586, 1411856335, 1235986345, 1782925031, 1198820766, 1332961379, 1216410350, 1395963072, 1337704484, 1101153787, 1246954810, 1949012737, 915054766, 1056675686, 1277910233, 1828156249, 1754724221, 1549946840, 1618691997, 1847546656, 958395793, 1502722408, 1801386329, 1461937614, 1915769650, 1935671186, 1188999783, 1019146114, 1289354858, 1576948149, 1328117283, 1462218620, 1367071112, 1731499414, 1457181038, 1481431715, 1610385822, 1084795355, 1127657772, 1779836416, 1611584772, 1914157201, 1349273798, 1420321089, 1500287444, 1939478952, 1037273257, 1285464375, 1948034156, 1877099889, 1647256772, 1766947416, 1622019567, 1853609766, 1743497998, 1125272382, 1752861379, 1712103266, 1902127614, 963286822, 1709588756, 915719845, 1695344402, 1633677426, 1688010576, 1269759954, 1641784649, 1538421544, 1775798953, 1724828336, 1533148072, 1394233200, 1687747991, 1367492204, 1579072440, 1653269530, 1172977235, 934384661, 1002006534, 1668311317, 1092769117, 1776208159, 1598372515, 1676880377, 1948240887, 1197863393, 1233009570, 1161023614, 931986087, 1354572823, 1963714460, 1099742979, 1461542841, 1639227745, 1656579631
		, 902289562, 906381055, 906500465, 906855752, 910650378, 911653167, 915338737, 918923773, 921242046, 923034772, 924074962, 924460986, 928766138, 929996248, 931147643, 940934529, 942902883, 944792500, 948000712, 951948909, 954121391, 955615516, 956461019, 961357961, 966757816, 969770935, 970625104, 972775731, 977264678, 980430910, 982685942, 992004186, 1007323105, 1010210146, 1010373132, 1015751492, 1030310960, 1033719349, 1035782987, 1036984625, 1037607761, 1039813292, 1040284544, 1051373464, 1054833014, 1055340235, 1058086306, 1059751140, 1076712343, 1084658057, 1093791155, 1095480946, 1101991611, 1105259803, 1105384363, 1107863371, 1122414232, 1128095624, 1139577401, 1141888373, 1143305521, 1146537391, 1146984905, 1149773926, 1153213749, 1167860538, 1172897751, 1179035930, 1180575780, 1187634806, 1194799529, 1197937831, 1205631707, 1206995187, 1207582827, 1208808765, 1224074232, 1242810573, 1244856817, 1248640878, 1249410513, 1266006209, 1277636871, 1282399422, 1284093407, 1292515846, 1309361384, 1312019618, 1313532882, 1325750291, 1329205122, 1331077624, 1333288562, 1339736258, 1342922916, 1361578247, 1363111969, 1367152140, 1385680495, 1387484314, 1396695914, 1401732008, 1405922573, 1407622044, 1407678047, 1408259293, 1412385554, 1414312878, 1414509548, 1415473642, 1433868717, 1442069811, 1444720629, 1445865685, 1446262222, 1447451563, 1448502859, 1451886431, 1452302995, 1454156078, 1467641972, 1469810936, 1470088654, 1473904816, 1481145931, 1481172079,
		1487804724, 1492584985, 1493002524, 1493800076, 1499086526, 1504399428, 1510892304, 1511003394, 1515526835, 1516844858, 1521695289, 1524815388, 1527092600, 1531661710, 1533671076, 1539984074, 1541830930, 1542023702, 1557161168, 1563370913, 1564790919, 1568435497, 1574092865, 1583303434, 1584702168, 1590595146, 1594985510, 1598223508, 1598674366, 1599898087, 1600678529, 1602667742, 1614986509, 1620724315, 1633395969, 1635032351, 1640437768, 1641000844, 1641713021, 1643078566, 1646405229, 1647273479, 1649010534, 1650353473, 1652541461, 1654058130, 1655452638, 1655578152, 1661945416, 1663895738, 1670358536, 1675609692, 1680549958, 1684116412, 1687596853, 1689327808, 1689545829, 1692264277, 1694711003, 1695275580, 1695807038, 1701319978, 1703489437, 1706328302, 1708814517, 1711972574, 1712153005, 1714089999, 1715179739, 1715389240, 1717276002, 1717789711, 1731316085, 1731795945, 1734918267, 1740561726, 1740615847, 1743273495, 1744945011, 1745208045, 1746315765, 1751140756, 1758120551, 1758642618, 1758847055, 1759640977, 1760953285, 1773097933, 1781961527, 1790012722, 1790519552, 1794995728, 1797480981, 1800214685, 1801492606, 1801555281, 1805737599, 1814185033, 1821243248, 1838522279, 1840457668, 1840895284, 1845189135, 1855184640, 1857893398, 1859432147, 1862873092, 1868229824, 1874859885, 1877947952, 1882742369, 1885594322, 1887411101, 1893078719, 1895799111, 1902708390, 1913116577, 1913119731, 1923160200, 1930261209, 1931136906, 1932377606, 1932606295, 1939258129, 1944376601, 1946151202, 1948551640, 1961299449, 1963499999, 1969322977 // 512 until now
		/// 512 until now
		, 184380991, 364361327, 1013816658, 162540129, 1006629947, 820991093, 121321928, 1013559041, 299154204, 638747492, 450455716, 846065816, 992609100, 264355847, 370052850, 350747808, 487102234, 1103331369, 601245412, 1129147095, 353516860, 491469084, 964096337, 1000205248, 599931720, 221607475, 859002161, 715319074, 1051650106, 709459784, 444889634, 607136391, 180997873, 125210423, 341906151, 1130571710, 1050370226, 639113824, 930576356, 853754713, 747091875, 305276201, 175157666, 488780592, 890071377, 649308794, 707793745, 103552988, 553937195, 968168000, 403858753, 1142203453, 601815813, 817444843, 808427368, 920508917, 125427862, 1022099695, 127349728, 151976426, 914953465, 1063551814, 848652646, 801999304, 108928304, 358824940, 854541788, 159770493, 170036380, 210949474, 237177031, 640718779, 598417031, 1061617197, 195737042, 932062329, 895868315, 415223636, 456699721, 694848371, 1006208616, 1097122533, 586834078, 568048805, 279509473, 856210032, 903215336, 696297684, 328286175, 891786634, 833500511, 1002659845, 1038555549, 1093228619, 120448738, 1058455556, 473637947, 245162448, 540509553, 624472798, 817302331, 125743803, 123601843, 863042919, 1029688071, 611435438, 245814385, 852598197, 911344489, 822406100, 222759449, 141900195, 470211089, 938596184, 481044540, 901913936, 1032842514, 391712235, 378254608, 1084705181, 584701285, 1024002370, 832035055, 1138627250, 518666597, 179821462, 129710294, 657149562,
		169897810, 574940707, 1146839271, 1067127586, 611856335, 435986345, 982925031, 398820766, 532961379, 416410350, 595963072, 537704484, 301153787, 446954810, 101529089, 115054766, 256675686, 477910233, 1028156249, 954724221, 749946840, 818691997, 1047546656, 158395793, 702722408, 1001386329, 661937614, 1115769650, 1135671186, 388999783, 219146114, 489354858, 776948149, 528117283, 662218620, 567071112, 931499414, 657181038, 681431715, 810385822, 284795355, 327657772, 979836416, 811584772, 1114157201, 549273798, 620321089, 700287444, 1139478952, 237273257, 485464375, 100550508, 1077099889, 847256772, 966947416, 822019567, 1053609766, 943497998, 325272382, 952861379, 912103266, 1102127614, 163286822, 909588756, 115719845, 895344402, 833677426, 888010576, 469759954, 841784649, 738421544, 975798953, 924828336, 733148072, 594233200, 887747991, 567492204, 779072440, 853269530, 372977235, 134384661, 202006534, 868311317, 292769117, 976208159, 798372515, 876880377, 100757239, 397863393, 433009570, 361023614, 131986087, 554572823, 116230812, 299742979, 661542841, 839227745, 856579631, 723809033, 1109380538, 604406210, 505399418, 1088954293, 309910015, 408294945, 410255267, 246548561, 516688668, 710019787, 249271121, 306526923, 292841325, 162654703, 894285874, 433992244, 957836177, 1019807265, 455954039, 980685122, 820353257, 180485336, 663156819, 771255503, 819434525, 233031920, 1028735104, 429270616, 125959832,
		768435497, 128766138, 1005737599, 847273479, 1102708390, 774092865, 1131136906, 911972574, 448640878, 820724315, 207323105, 1059432147, 906328302, 757161168, 123034772, 1082742369, 387634806, 151948909, 124074962, 880549958, 169770935, 140934529, 944945011, 1132377606, 235782987, 142902883, 1021243248, 349773926, 654156078, 615473642, 889545829, 115338737, 408808765, 1113119731, 742023702, 254833014, 121242046, 116016351, 799898087, 1123160200, 101067992, 741830930, 210210146, 118923773, 1057893398, 341888373, 908814517, 681172079, 509361384, 644720629, 343305521, 482399422, 1146151202, 711003394, 973097933, 693800076, 934918267, 1139258129, 1113116577, 889327808, 914089999, 379035930, 407582827, 1062873092, 802667742, 305259803, 605922573, 1095799111, 648502859, 652302995, 567152140, 895275580, 1000214685, 561578247, 525750291, 129996248, 529205122, 800678529, 585680495, 784702168, 764790919, 210373132, 959640977, 721695289, 763370913, 339577401, 731661710, 798674366, 1038522279, 1087411101, 512019618, 846405229, 645865685, 237607761, 394799529, 612385554, 307863371, 106500465, 733671076, 301991611, 841000844, 903489437, 367860538, 716844858, 106381055, 131147643, 887596853, 843078566, 295480946, 172775731, 833395969, 405631707, 854058130, 444856817, 230310960, 946315765, 667641972, 958120551, 424074232, 1130261209, 917789711, 106855752, 293791155, 239813292, 1093078719, 646262222, 651886431, 192004186,
		1040457668, 233719349, 724815388, 710892304, 466006209, 895807038, 673904816, 539736258, 180430910, 912153005, 492515846, 397937831, 794985510, 255340235, 647451563, 166757816, 1014185033, 259751140, 170625104, 1040895284, 894711003, 739984074, 790595146, 835032351, 406995187, 1001555281, 997480981, 699086526, 814986509, 449410513, 442810573, 693002524, 284658057, 940615847, 715526835, 328095624, 901319978, 144792500, 346537391, 852541461, 251373464, 608259293, 148000712, 692584985, 855452638, 161357961, 633868717, 154121391, 945208045, 177264678, 111653167, 353213749, 943273495, 542922916, 960953285, 670088654, 951140756, 669810936, 477636871, 121839329, 1055184640, 102289562, 642069811, 322414232, 156461019, 870358536, 305384363, 917276002, 840437768, 850353473, 931316085, 533288562, 958847055, 681145931, 124460986, 940561726, 915179739, 614312878, 861945416, 990519552, 884116412, 182685942, 994995728, 915389240, 849010534, 687804724, 601732008, 855578152, 236984625, 841713021, 346984905, 1132606295, 372897751, 596695914, 513532882, 1045189135, 113815801, 276712343, 704399428, 484093407, 587484314, 380575780, 215751492, 1144376601, 258086306, 981961527, 155615516, 892264277, 875609692, 727092600, 863895738, 614509548, 531077624, 798223508, 1077947952, 1001492606, 110650378, 958642618, 990012722, 1074859885, 783303434, 563111969, 607622044, 607678047, 1085594322, 240284544, 931795945, 1068229824
	};
	
	char c[100];
	char *str;
	unsigned char uc[100], output[100];
	unsigned char *ustr;
	unsigned int hash = 0, part[4] = { 0, 0, 0, 0 };
	int i, j;

	input = input ^ prime[num - 1];
	input = input + num;
	str = itoa(input, c, 10);
	ustr = uc;
	i = 0;

	while (str[i] != NULL) {
		ustr[i] = (unsigned char)str[i];
		i++;
	}
	ustr[i] = NULL;
	md5(uc, i, output);

	for (i = 0; i<4; i++)
		for (j = 4 * i; j<4 * i + 4; j++)
			part[i] = part[i] ^ output[j];
	hash = (part[0] << 24) + (part[1] << 16) + (part[2] << 8) + part[3];

	hash = hash % maxVal;
	return hash;
}
unsigned int RandInt(unsigned int lo, unsigned int hi){
	// return lo ~ hi (smallest in 32 bit integer ~ biggest in 32 bit integer)
	unsigned int t1, t2;
	t1 = rand();
	t1 = t1 << 15;
	t2 = rand();
	if (t1 + t2 < 0) {
		printf("\nerror in RandInt");
		exit(0);
	}
	return ((t1 + t2) % (hi - lo + 1)) + lo;
}

int main(int argc, char* argv[]){   
	/*
	*	Must Excute with testcase number in argv[1]
	*/
	if (argc < 2){		// No Testcase number input
		printf("usage: %s [testcases_number]\n", argv[0]);
		exit(-1);
	}
	srand((unsigned int)time(NULL));			// Seed for rand()
	unsigned int maxValue;						// MaxValue input (argv[1])
	sscanf(argv[1], "%u", &maxValue);			// Convert string(argv[1]) to unsigned integer(maxValue)
	
	unsigned int* collisionCount = new unsigned int[maxValue];		// Compute rate of collision
	memset(collisionCount, 0, sizeof(int)*maxValue);			// Set all collisionCount array member to FALSE

	std::set<unsigned int> randomSet;						// Set data struct for random number array ( do not save same number .....)
	std::set<unsigned int> ::iterator iter;					// Iterator for set data struct(randomSet)

	for (; randomSet.size() != maxValue;)			// Random number insert in set 
		randomSet.insert(RandInt(LOWER_NUMBER, UPPER_NUMBER));
		
	int *depthSet = new int[MAX_DEPTH];
	memset(depthSet, 0, sizeof(int)*MAX_DEPTH);
	/*
	*	clock_t start, end  : Measure total time to excute hash function
	*	start -> save time before running hash function 
	*	end -> save time later running hash function
	*	Then, (end - start) means total time(sec, beacause of divide by CLOCKS_PER_SEC)
	*/	
	clock_t start, end;			
	start = clock();
	// Measurement start
	for (iter = randomSet.begin(); iter != randomSet.end(); iter++)
		collisionCount[hash(0, *iter, maxValue)]++;
	// Measurement end
	end = clock();
	// max Depth in hash function ( means chain)

	// mex depth in hash function
	int maxDepth = 0;
	// make depthSet array 
	for (int i = 0; i < randomSet.size(); i++){
		depthSet[collisionCount[i]]++;
		if (maxDepth <= collisionCount[i]) maxDepth = collisionCount[i];		
	}	

	// Show total time
	std::cout << "----------------------------------" << std::endl;
	std::cout << "Complete Funcion!" << std::endl;
	std::cout << "Total data : " << randomSet.size() << std::endl;
	std::cout << "Total time : ";
	printf("%.6fsec\n", (double)(end - start) / CLOCKS_PER_SEC);
	std::cout << "----------------------------------" << std::endl;
	// Calcurate rate of collision in hash function
	double count = 0;
	for (unsigned int i = 0; i < randomSet.size(); i++)
		if (collisionCount[i])
			count++;

	// Show rate of collision in hash function
	std::cout << "----------------------------------" << std::endl;
	std::cout << "Collision Rate : " << (count / maxValue) * 100 << "%" << std::endl;
	std::cout << "----------------------------------" << std::endl;

	// Show each depth in hash function
	std::cout << "----------------------------------" << std::endl;
	for (int i = 0; i <= maxDepth; i++)
		if(depthSet[i]) std::cout <<"Depth "<<i<<" : "<< depthSet[i] << " ("<<(((double)depthSet[i])/(double)randomSet.size())*100<<"%)"<<std::endl;
	std::cout << "Max depth in hash function : " << maxDepth << std::endl;
	std::cout << "----------------------------------" << std::endl;

	delete[] collisionCount;
	delete[] depthSet;
}
