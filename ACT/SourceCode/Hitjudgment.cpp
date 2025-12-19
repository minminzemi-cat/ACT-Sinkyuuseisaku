#include "Hitjudgment.h"
#include "cmath"

CHitjudgment::CHitjudgment()
{

}

CHitjudgment::~CHitjudgment()
{

}
//‰~‚Æ‰~‚Ì“–‚½‚è”»’è
bool CHitjudgment::collisionSpher(
	int r1x, int r1y, int Aw, int Ah,
	int r2x, int r2y, int Bw, int Bh)
{
	
   int i=sqrt(((r1x+Aw/2)-(r2x+ Bw/2))* ((r1x + Aw / 2) - (r2x + Bw / 2))
			+((r1y+Ah/2)-(r2y+Bh/2))* ((r1y + Ah / 2) - (r2y + Bh / 2)));
   int j = Aw/2 + Bw/2;
	if (j>=i)
	{
		//–½’†‚µ‚½‚Æ‚«
		return true;
	} 
	return false;
}

//‰~‚Æ‰~‚Ì“–‚½‚è”»’è
bool CHitjudgment::collisionDetection(
	int Ax, int Ay, int Aw, int Ah, 
	int Bx, int By, int Bw, int Bh)
{

	if ((
		Ax <= Bx + Bw) && (Bx <= Ax + Aw)
		&& (Ay <= By + Bh) && (By <= Ay + Ah))
	{
		//–½’†‚µ‚½‚Æ‚«
		return true;
	}
	//ŠO‚ê‚½Žž
	return false;
}


