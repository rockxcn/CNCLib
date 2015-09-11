////////////////////////////////////////////////////////
/*
  This file is part of CNCLib - A library for stepper motors.

  Copyright (c) 2013-2015 Herbert Aitenbichler

  CNCLib is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  CNCLib is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.
  http://www.gnu.org/licenses/
*/
////////////////////////////////////////////////////////

#include "stdafx.h"
#include <math.h>

#include "..\MsvcStepper\MsvcStepper.h"
#include "TestTools.h"

#include "..\..\..\sketch\libraries\CNCLib\src\Matrix4x4.h"
#include "DenavitHartenberg.h"

////////////////////////////////////////////////////////////////////////////////////////

int _tmain(int /* argc */, _TCHAR* /* argv */ [])
{




	//////////////////////////////////////////

	{
		/*
		float alpha = M_PI / 5;
		float theta = M_PI / 6;
		float a = 1.123456;
		float d = 4.321;
		CMatrix4x4<float> T1; T1.InitDenavitHartenberg1Rot(theta);
		CMatrix4x4<float> T2; T2.InitDenavitHartenberg3Trans(a);

		CMatrix4x4<float> T3 = T1*T2;

		CMatrix4x4<float> T4; T4.InitDenavitHartenberg1Rot3Trans(theta, a);

		if (!T4.IsEqual(T3, 0.00001))
		{
			printf("Error InitDenavitHartenberg Combi\n");
		}
		*/
	}

	//////////////////////////////////////////
	{
		CDenavitHartenberg dh;

		struct STest
		{
			float posxyz[3];
			float angles[3];
			float allowdiff;
		};
		float allowdiff = 0.0001;

		STest values[] = {

			{ { 1.000000, 200.000000, 105.000000 }, { 1.008016, 1.240501, 1.565796 }, allowdiff },
			{ { 0.000000, 200.000000, 105.000000 }, { 1.008028, 1.240480, 1.570796 }, allowdiff },
			{ { -1.000000, 200.000000, 105.000000 }, { 1.008016, 1.240501, 1.575796 }, allowdiff },
			{ { 1.000000, -200.000000, 105.000000 }, { 1.008016, 1.240501, -1.565796 }, allowdiff },
			{ { 0.000000, -200.000000, 105.000000 }, { 1.008028, 1.240480, -1.570796 }, allowdiff },
			{ { -1.000000, -200.000000, 105.000000 }, { 1.008016, 1.240501, -1.575796 }, allowdiff },
			{ { 322.000000, 0.000000, 105.000000 }, { 0.000000, 3.1415926, 0.000000 }, allowdiff },
			{ { 182.000000, 0.000000, 245.000000 }, { 1.5707963, 1.5707963, 0.000000 }, allowdiff },
			{ { 200.000000, 0.000000, 105.000000 }, { 1.008028, 1.240480, 0.000000 }, allowdiff },
			{ { 200.000000, 100.000000, 105.000000 }, { 0.893337, 1.447827, 0.463648 }, allowdiff },
			{ { 100.000000, 100.000000, 105.000000 }, { 1.281145, 0.778904, 0.785398 }, allowdiff },
			{ { 50.000000, 0.000000, 105.000000 }, { 2.158301, 0.109737, 0.000000 }, allowdiff },
			{ { 60.000000, 0.000000, 105.000000 }, { 1.885989, 0.188764, 0.000000 }, allowdiff },
			{ { 70.000000, 0.000000, 105.000000 }, { 1.741626, 0.262326, 0.000000 }, allowdiff },
			{ { 80.000000, 0.000000, 105.000000 }, { 1.642572, 0.334292, 0.000000 }, allowdiff },
			{ { 90.000000, 0.000000, 105.000000 }, { 1.565082, 0.405774, 0.000000 }, allowdiff },
			{ { 100.000000, 0.000000, 105.000000 }, { 1.499511, 0.477271, 0.000000 }, allowdiff },
			{ { 110.000000, 0.000000, 105.000000 }, { 1.441148, 0.549075, 0.000000 }, allowdiff },
			{ { 120.000000, 0.000000, 105.000000 }, { 1.387389, 0.621401, 0.000000 }, allowdiff },
			{ { 130.000000, 0.000000, 105.000000 }, { 1.336663, 0.694426, 0.000000 }, allowdiff },
			{ { 140.000000, 0.000000, 105.000000 }, { 1.287949, 0.768320, 0.000000 }, allowdiff },
			{ { 150.000000, 0.000000, 105.000000 }, { 1.240540, 0.843252, 0.000000 }, allowdiff },
			{ { 160.000000, 0.000000, 105.000000 }, { 1.193915, 0.919401, 0.000000 }, allowdiff },
			{ { 170.000000, 0.000000, 105.000000 }, { 1.147671, 0.996961, 0.000000 }, allowdiff },
			{ { 180.000000, 0.000000, 105.000000 }, { 1.101470, 1.076153, 0.000000 }, allowdiff },
			{ { 190.000000, 0.000000, 105.000000 }, { 1.055015, 1.157228, 0.000000 }, allowdiff },
			{ { 200.000000, 0.000000, 105.000000 }, { 1.008028, 1.240480, 0.000000 }, allowdiff },
			{ { 210.000000, 0.000000, 105.000000 }, { 0.960228, 1.326261, 0.000000 }, allowdiff },
			{ { 220.000000, 0.000000, 105.000000 }, { 0.911315, 1.414998, 0.000000 }, allowdiff },
			{ { 230.000000, 0.000000, 105.000000 }, { 0.860954, 1.507220, 0.000000 }, allowdiff },
			{ { 240.000000, 0.000000, 105.000000 }, { 0.808743, 1.603603, 0.000000 }, allowdiff },
			{ { 250.000000, 0.000000, 105.000000 }, { 0.754183, 1.705034, 0.000000 }, allowdiff },
			{ { 260.000000, 0.000000, 105.000000 }, { 0.696615, 1.812717, 0.000000 }, allowdiff },
			{ { 270.000000, 0.000000, 105.000000 }, { 0.635121, 1.928367, 0.000000 }, allowdiff },
			{ { 280.000000, 0.000000, 105.000000 }, { 0.568332, 2.054579, 0.000000 }, allowdiff },
			{ { 290.000000, 0.000000, 105.000000 }, { 0.494008, 2.195630, 0.000000 }, allowdiff },
			{ { 300.000000, 0.000000, 105.000000 }, { 0.407949, 2.359574, 0.000000 }, allowdiff },
			{ { 310.000000, 0.000000, 105.000000 }, { 0.300103, 2.565728, 0.000000 }, allowdiff },
			{ { 320.000000, 0.000000, 105.000000 }, { 0.122047, 2.907177, 0.000000 }, allowdiff },
			{ { 200.000000, 0.000000, 50.000000 }, { 0.653714, 1.314741, 0.000000 }, allowdiff },
			{ { 200.000000, 0.000000, 150.000000 }, { 1.238929, 1.290373, 0.000000 }, allowdiff },
			{ { 200.000000, 50.000000, 150.000000 }, { 1.201563, 1.342109, 0.244979 }, allowdiff },
			{ { -1234 } } };

		for (STest* v = values; v->posxyz[0] != -1234; v++)
		{
			float out[3];
			dh.ToPosition(v->angles, out);

			bool print = false;

			for (unsigned char n = 0; n < 3; n++)
			{
				if (!CMatrix4x4<float>::IsEqual(out[n], v->posxyz[n], v->allowdiff))
				{
					if (!print)
						printf("Error InitDenavitHartenberg #20: %.2f:%.2f:%.2f ", v->posxyz[0], v->posxyz[1], v->posxyz[2]);
					printf("%f=>%f(%f) ", out[n], v->angles[n], out[n] - v->angles[n]);
					print = true;
				}
			}
			if (print)
				printf("\n");
		}
	}

	//////////////////////////////////////////
	{
		CDenavitHartenberg dh;
		struct STest
		{
			float posxyz[3];
			float angles[3];
			float allowdiff;
		};
		float allowdiff = 0.001;

		STest values[] = {


			{ { 182.000000, 0.000000, 245.000000 }, { 1.5707963, 1.5707963, 0.000000 }, allowdiff },
			{ { 0.000000, -200.000000, 105.000000 }, { 1.008028, 1.240480, -1.570796 }, allowdiff },
//			{ { 320.000000, 0.000000, 105.000000 }, { 0.122047, 2.907177, 0.000000 }, allowdiff },
			{ { 322.000000, 0.000000, 105.000000 }, { 0.000000, 3.1415926, 0.000000 }, allowdiff },

			{ { 1.000000, 200.000000, 105.000000 }, { 1.008016, 1.240501, 1.565796 }, allowdiff },
			{ { 0.000000, 200.000000, 105.000000 }, { 1.008028, 1.240480, 1.570796 }, allowdiff },
			{ { -1.000000, 200.000000, 105.000000 }, { 1.008016, 1.240501, 1.575796 }, allowdiff },
			{ { 1.000000, -200.000000, 105.000000 }, { 1.008016, 1.240501, -1.565796 }, allowdiff },
			{ { 0.000000, -200.000000, 105.000000 }, { 1.008028, 1.240480, -1.570796 }, allowdiff },
			{ { -1.000000, -200.000000, 105.000000 }, { 1.008016, 1.240501, -1.575796 }, allowdiff },
			{ { 322.000000, 0.000000, 105.000000 }, { 0.000000, 3.1415926, 0.000000 }, allowdiff },
			{ { 182.000000, 0.000000, 245.000000 }, { 1.5707963, 1.5707963, 0.000000 }, allowdiff },
			{ { 200.000000, 0.000000, 105.000000 }, { 1.008028, 1.240480, 0.000000 }, allowdiff },
			{ { 200.000000, 100.000000, 105.000000 }, { 0.893337, 1.447827, 0.463648 }, allowdiff },
			{ { 100.000000, 100.000000, 105.000000 }, { 1.281145, 0.778904, 0.785398 }, allowdiff },
			{ { 50.000000, 0.000000, 105.000000 }, { 2.158301, 0.109737, 0.000000 }, allowdiff },
			{ { 60.000000, 0.000000, 105.000000 }, { 1.885989, 0.188764, 0.000000 }, allowdiff },
			{ { 70.000000, 0.000000, 105.000000 }, { 1.741626, 0.262326, 0.000000 }, allowdiff },
			{ { 80.000000, 0.000000, 105.000000 }, { 1.642572, 0.334292, 0.000000 }, allowdiff },
			{ { 90.000000, 0.000000, 105.000000 }, { 1.565082, 0.405774, 0.000000 }, allowdiff },
			{ { 100.000000, 0.000000, 105.000000 }, { 1.499511, 0.477271, 0.000000 }, allowdiff },
			{ { 110.000000, 0.000000, 105.000000 }, { 1.441148, 0.549075, 0.000000 }, allowdiff },
			{ { 120.000000, 0.000000, 105.000000 }, { 1.387389, 0.621401, 0.000000 }, allowdiff },
			{ { 130.000000, 0.000000, 105.000000 }, { 1.336663, 0.694426, 0.000000 }, allowdiff },
			{ { 140.000000, 0.000000, 105.000000 }, { 1.287949, 0.768320, 0.000000 }, allowdiff },
			{ { 150.000000, 0.000000, 105.000000 }, { 1.240540, 0.843252, 0.000000 }, allowdiff },
			{ { 160.000000, 0.000000, 105.000000 }, { 1.193915, 0.919401, 0.000000 }, allowdiff },
			{ { 170.000000, 0.000000, 105.000000 }, { 1.147671, 0.996961, 0.000000 }, allowdiff },
			{ { 180.000000, 0.000000, 105.000000 }, { 1.101470, 1.076153, 0.000000 }, allowdiff },
			{ { 190.000000, 0.000000, 105.000000 }, { 1.055015, 1.157228, 0.000000 }, allowdiff },
			{ { 200.000000, 0.000000, 105.000000 }, { 1.008028, 1.240480, 0.000000 }, allowdiff },
			{ { 210.000000, 0.000000, 105.000000 }, { 0.960228, 1.326261, 0.000000 }, allowdiff },
			{ { 220.000000, 0.000000, 105.000000 }, { 0.911315, 1.414998, 0.000000 }, allowdiff },
			{ { 230.000000, 0.000000, 105.000000 }, { 0.860954, 1.507220, 0.000000 }, allowdiff },
			{ { 240.000000, 0.000000, 105.000000 }, { 0.808743, 1.603603, 0.000000 }, allowdiff },
			{ { 250.000000, 0.000000, 105.000000 }, { 0.754183, 1.705034, 0.000000 }, allowdiff },
			{ { 260.000000, 0.000000, 105.000000 }, { 0.696615, 1.812717, 0.000000 }, allowdiff },
			{ { 270.000000, 0.000000, 105.000000 }, { 0.635121, 1.928367, 0.000000 }, allowdiff },
			{ { 280.000000, 0.000000, 105.000000 }, { 0.568332, 2.054579, 0.000000 }, allowdiff },
			{ { 290.000000, 0.000000, 105.000000 }, { 0.494008, 2.195630, 0.000000 }, allowdiff },
			{ { 300.000000, 0.000000, 105.000000 }, { 0.407949, 2.359574, 0.000000 }, allowdiff },
			{ { 310.000000, 0.000000, 105.000000 }, { 0.300103, 2.565728, 0.000000 }, allowdiff },
			{ { 320.000000, 0.000000, 105.000000 }, { 0.122047, 2.907177, 0.000000 }, allowdiff },
			{ { 200.000000, 0.000000, 50.000000 }, { 0.653714, 1.314741, 0.000000 }, allowdiff },
			{ { 200.000000, 0.000000, 150.000000 }, { 1.238929, 1.290373, 0.000000 }, allowdiff },
			{ { 200.000000, 50.000000, 150.000000 }, { 1.201563, 1.342109, 0.244979 }, allowdiff },
			{ { -1234 } } };


		for (STest* v = values; v->posxyz[0] != -1234; v++)
		{
			bool print = false;
			bool printprint = false;

			float out[3] = { 0, 0, 0 };
			dh.FromPosition(v->posxyz, out,0.001);

			for (unsigned char n = 0; n < 3; n++)
			{
				if (!CMatrix4x4<float>::IsEqual(out[n], v->angles[n], v->allowdiff))
				{
					if (!print)
						printf("Error InitDenavitHartenberg #21: %.2f:%.2f:%.2f\t", v->posxyz[0], v->posxyz[1], v->posxyz[2]);
					
					printf("%f=>%f(%f)\t", out[n], v->angles[n], out[n] - v->angles[n]);
					print = true;
					printprint = true;
				}
			}

			if (print)
				printf("\n");
			
			print = false;

			float posxyz[3];
			dh.ToPosition(out, posxyz);

			for (unsigned char n = 0; n < 3; n++)
			{
				if (!CMatrix4x4<float>::IsEqual(v->posxyz[n], posxyz[n], 000.1))
				{
					if (!print)
						printf("Error InitDenavitHartenberg #22: %.2f:%.2f:%.2f\t", v->posxyz[0], v->posxyz[1], v->posxyz[2]);

					printf("%f=>%f(%f)\t", posxyz[n], v->posxyz[n], posxyz[n] - v->posxyz[n]);
					print = true;
					printprint = true;
				}
			}

			if (print)
				printf("\n");

			if (printprint)
				printf("\n");
		}
	}
}
