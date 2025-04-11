//-----------------------------------------------------------------------------------//
// Nom du projet 		: Projet 2 - Calculs Trigo
// Nom du fichier 		: FctCalculTrigo.c
// Date de cr�ation 	: 14.02.2024
// Date de modification : 14.02.2024
//
// Auteur 				: Philou (Ph. Bovey)
//
// Description          : 
//
// Remarques			: voir donnee de l'�preuve            
//----------------------------------------------------------------------------------//

//-- definission pour utiliser la lib math sous VS --// 
#define _USE_MATH_DEFINES

//--- librairie standart ---//
#include <stdio.h>                  // entr�e - sortie
#include <stdlib.h>					// fonctions syst�me
#include <math.h>

//--- librairie perso ---//
#include "CalculTrigo.h"

/* ----------------------------------------------------------------------------------
// -> NOM FCT					: InitialiserStructure 
// -> PARAMETRES ENTRES			: 
// -> PARAMETRE SORTIE			: e_validation 
// -> PARAMETRE IN/OUT -> ptr	: str_triangleRectangle pt_strTriangle 
// -> description				: tous les champs de la structure seront mis � z�ro
 ----------------------------------------------------------------------------------*/
e_validation InitialiserStructure(str_triangleRectangle *pt_strTriangle)
{
	//-- d�claration variables --// 
	//-- pirmaire --// 

	//-- enumeration --// 
	e_validation valRetour = nok;

	//-- boucle pour initilaiser le tableau des angles --//
	for (char i = 0; i < 4; i++)
	{
		pt_strTriangle->tb_Angle[i] = 0;
	}
	//-- initialisation des cot�s -> adj - hyp - opp --// 
	pt_strTriangle->triangle_s.adjacent = 0;
	pt_strTriangle->triangle_s.hypotenuse = 0;
	pt_strTriangle->triangle_s.oppose = 0;
	//-- initialisation des champs de air et perim�tres --// 
	pt_strTriangle->air = 0;
	pt_strTriangle->perimetre = 0;

	//-- validation -> de la fct --// 
	if
		(
		(pt_strTriangle->tb_Angle[0] == 0) &&
		(pt_strTriangle->tb_Angle[1] == 0) &&
		(pt_strTriangle->tb_Angle[2] == 0) &&
		(pt_strTriangle->tb_Angle[3] == 0) &&
		(pt_strTriangle->triangle_s.adjacent == 0) &&
		(pt_strTriangle->triangle_s.hypotenuse == 0) &&
		(pt_strTriangle->triangle_s.oppose == 0) &&
		(pt_strTriangle->air == 0) &&
		(pt_strTriangle->perimetre == 0)
		)
	{
		valRetour = ok;
	}
	else
	{
		valRetour = nok;
	}

	//-- valeur � retourner --// 
	return valRetour;
}
/* ----------------------------------------------------------------------------------
// -> NOM FCT					: Conversion_DegRad
// -> PARAMETRES ENTRES			:
// -> PARAMETRE SORTIE			: 
// -> PARAMETRE IN/OUT -> ptr	: str_triangleRectangle pt_strTriangle
// -> description				: depuis un angle en degr� -> d�terminer sa valeur 
//								  en radian 
 ----------------------------------------------------------------------------------*/
void Conversion_DegRad(str_triangleRectangle* pt_strTriangle)
{
	//-- test si angle � convertir --//
	
	//-- test si angle alpha � convertir --//
	if (pt_strTriangle->tb_Angle[0] != 0)
	{
		pt_strTriangle->tb_Angle[1] = (float)(M_PI / 180) * pt_strTriangle->tb_Angle[0];
	}
	//-- test si angle beta � convertir --//
	if (pt_strTriangle->tb_Angle[2] != 0)
	{
		pt_strTriangle->tb_Angle[3] = (float)(M_PI / 180) * pt_strTriangle->tb_Angle[2];
	}

}
/* ----------------------------------------------------------------------------------
// -> NOM FCT					: Conversion_RadDeg
// -> PARAMETRES ENTRES			:
// -> PARAMETRE SORTIE			:
// -> PARAMETRE IN/OUT -> ptr	: str_triangleRectangle pt_strTriangle
// -> description				: depuis un angle en radian -> d�terminer sa valeur
//								  en degr�
 ----------------------------------------------------------------------------------*/
void Conversion_RadDeg(str_triangleRectangle* pt_strTriangle)
{
	//-- test si angle � convertir --//

	//-- test si angle alpha � convertir --//
	if (pt_strTriangle->tb_Angle[1] != 0)
	{
		pt_strTriangle->tb_Angle[0] = ((float)( 180 / M_PI) * pt_strTriangle->tb_Angle[1]);
	}
	//-- test si angle beta � convertir --//
	if (pt_strTriangle->tb_Angle[3] != 0)
	{
		pt_strTriangle->tb_Angle[2] = ((float)(180 / M_PI) * pt_strTriangle->tb_Angle[3]);
	}

}
/* ----------------------------------------------------------------------------------
// -> NOM FCT					: CalculAllAngles
// -> PARAMETRES ENTRES			:
// -> PARAMETRE SORTIE			: e_validation
// -> PARAMETRE IN/OUT -> ptr	: str_triangleRectangle pt_strTriangle
// -> description				: si angle rentr� alors alors d�termine le 2�me angle 
 ----------------------------------------------------------------------------------*/
e_validation CalculerAllAngles(str_triangleRectangle* pt_strTriangle)
{
	//-- enumeration --// 
	e_validation valRetour = nok;

	//-- variable locale --//
	double sinAlpha;
	double tanAlpha;
	double cosAlpha;
	double Alpha;
	//-- test si un angle a �t� d�finit alpha ou beta 
	if ((pt_strTriangle->tb_Angle[0] != 0) || (pt_strTriangle->tb_Angle[2] != 0))
	{
		if (pt_strTriangle->tb_Angle[0] != 0)
		{
			pt_strTriangle->tb_Angle[2] = 90 - (pt_strTriangle->tb_Angle[0]);
		}
		else if (pt_strTriangle->tb_Angle[2] != 0)
		{
			pt_strTriangle->tb_Angle[0] = 90 - (pt_strTriangle->tb_Angle[2]);
		}

		Conversion_DegRad(pt_strTriangle);
	}
	//-- si pas d'angle d�fini 	
	if ((pt_strTriangle->tb_Angle[0] == 0) && (pt_strTriangle->tb_Angle[2] == 0))
	{

		//-- si cot� non d�fini -> hypoth�nuse -> fonction trigo invers�e arctan 
		if (pt_strTriangle->triangle_s.hypotenuse == 0)
		{
			tanAlpha = ((double)pt_strTriangle->triangle_s.oppose / (double)pt_strTriangle->triangle_s.adjacent);
			Alpha = atan(tanAlpha);
			pt_strTriangle->tb_Angle[1] = (float)Alpha;
			//pt_strTriangle->tb_Angle[0] = (float)atan((double)pt_strTriangle->triangle_s.oppose/ (double)pt_strTriangle->triangle_s.adjacent);
			pt_strTriangle->tb_Angle[3] = (float)(M_PI / 2) - (pt_strTriangle->tb_Angle[1]);
		}
		//-- si cot� non d�fini -> oppos� -> fonction trigo invers�e arccos
		else if (pt_strTriangle->triangle_s.oppose == 0)
		{
			cosAlpha = ((double)pt_strTriangle->triangle_s.adjacent / (double)pt_strTriangle->triangle_s.hypotenuse);
			Alpha = acos(cosAlpha);
			pt_strTriangle->tb_Angle[1] = (float)Alpha;
			//pt_strTriangle->tb_Angle[0] = (float)acos((double)pt_strTriangle->triangle_s.adjacent/ (double)pt_strTriangle->triangle_s.hypotenuse);
			pt_strTriangle->tb_Angle[3] = (float)(M_PI / 2) - (pt_strTriangle->tb_Angle[1]);
		}
		//-- si cot� non d�fini -> adjacent -> fonction trigo invers�e arcsin
		else if (pt_strTriangle->triangle_s.adjacent == 0)
		{
			sinAlpha = ((double)pt_strTriangle->triangle_s.oppose / (double)pt_strTriangle->triangle_s.hypotenuse);
			Alpha = asin(sinAlpha);
			pt_strTriangle->tb_Angle[1] = (float)Alpha;
			//pt_strTriangle->tb_Angle[1] = (float)asin((double)pt_strTriangle->triangle_s.oppose/ (double)pt_strTriangle->triangle_s.hypotenuse);
			pt_strTriangle->tb_Angle[3] = (float)(M_PI / 2) - (pt_strTriangle->tb_Angle[1]);
		}
		
		Conversion_RadDeg(pt_strTriangle);
	}

	//-- validation -> de la fct --// 
	if
		(
		(pt_strTriangle->tb_Angle[0] != 0) &&
		(pt_strTriangle->tb_Angle[1] != 0) &&
		(pt_strTriangle->tb_Angle[2] != 0) &&
		(pt_strTriangle->tb_Angle[3] != 0)
		)
	{
		valRetour = ok;
	}
	else
	{
		valRetour = nok;
	}

	//-- valeur � retourner --// 
	return valRetour;

}
/* ----------------------------------------------------------------------------------
// -> NOM FCT					: CalculerLongeursSgements
// -> PARAMETRES ENTRES			:
// -> PARAMETRE SORTIE			: e_validation
// -> PARAMETRE IN/OUT -> ptr	: str_triangleRectangle pt_strTriangle
// -> description				: calculer les diff�rents segments du triangle 
//								  [adjacent - hypoth�nuse - oppos�] 
//								  selon les param�tres ins�rer par l'utilisateur
 ----------------------------------------------------------------------------------*/
e_validation CalculerLongueurSegment(str_triangleRectangle* pt_strTriangle)
{
	//-- enumeration --// 
	e_validation valRetour = nok;

	//-- calcul de tous les angles -> appel de fct --// 
	CalculerAllAngles(pt_strTriangle);
	
	if (pt_strTriangle->triangle_s.hypotenuse != 0)
	{
		//-- test si sgement hypoth�nuse entr� 

				//Calcul -> cos(alpha) = adj / hyp => ... 
		pt_strTriangle->triangle_s.adjacent = cos(pt_strTriangle->tb_Angle[1]) * pt_strTriangle->triangle_s.hypotenuse;
	

				//Calcul -> sin(alpha) = opp / hyp => ...
		pt_strTriangle->triangle_s.oppose = sin(pt_strTriangle->tb_Angle[1]) * pt_strTriangle->triangle_s.hypotenuse;
	}
	else if (pt_strTriangle->triangle_s.adjacent != 0)
	{
		//-- test si sgement adjacent entr� 

				//Calcul -> cos(alpha) = adj/hyp => ...
		pt_strTriangle->triangle_s.hypotenuse =  pt_strTriangle->triangle_s.adjacent / cos(pt_strTriangle->tb_Angle[1]);

				//Calcul -> tan(alpha) = opp/adj => ...
		pt_strTriangle->triangle_s.oppose = tan(pt_strTriangle->tb_Angle[1]) * pt_strTriangle->triangle_s.adjacent;
	}
	else if (pt_strTriangle->triangle_s.oppose != 0)
	{
		//-- test si sgement oppos� entr�  

				//Calcul -> sin(alpha) = opp/hyp => ...
		pt_strTriangle->triangle_s.hypotenuse = pt_strTriangle->triangle_s.oppose / sin(pt_strTriangle->tb_Angle[1]);

				//Calcul -> tan(alpha) = opp/adj => ... 
		pt_strTriangle->triangle_s.adjacent = pt_strTriangle->triangle_s.oppose / tan(pt_strTriangle->tb_Angle[1]);
	}


	//-- validation -> de la fct --//
	if  (
		(pt_strTriangle->tb_Angle[0] != 0) &&
		(pt_strTriangle->tb_Angle[1] != 0) &&
		(pt_strTriangle->tb_Angle[2] != 0) &&
		(pt_strTriangle->tb_Angle[3] != 0) &&
		(pt_strTriangle->triangle_s.adjacent != 0) &&
		(pt_strTriangle->triangle_s.hypotenuse != 0) &&
		(pt_strTriangle->triangle_s.oppose != 0)
		)
	{
		valRetour = ok;
	}
	else
	{
		valRetour = nok;
	}

	//-- valeur � retourner --// 
	return valRetour;
}








