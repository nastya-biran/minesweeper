//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include <algorithm>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
struct Cletka
{
	int KolBomb;
	bool Opened;
	bool Checked;
	bool Mined;
};
int KolKl = 10;
Cletka Pole [100][100];
int BombVsego = 15;
int BombLeft = BombVsego;
int min = 0;
int sec = 0;

Graphics::TBitmap*BombPc;
Graphics::TBitmap*FlagPc;
Graphics::TBitmap *cl1 = new Graphics::TBitmap();
Graphics::TBitmap *cl2 = new Graphics::TBitmap();
Graphics::TBitmap *cl3 = new Graphics::TBitmap();
Graphics::TBitmap *cl4 = new Graphics::TBitmap();

//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm1::DrawCletka(int x, int y)
{
		if(x >= 10 || y >= 10)
        	return;
		if(Pole[x][y].Opened)
		{
			if((x + y) % 2 == 0)
			{
				Image1->Canvas->Draw(x*50,y*50,cl3);
			}
			else
			{
				Image1->Canvas->Draw(x*50,y*50,cl4);
			}
		}
		else
		{
            if((x + y) % 2 == 0)
			{
				Image1->Canvas->Draw(x*50,y*50,cl1);
			}
			else
			{
				Image1->Canvas->Draw(x*50,y*50,cl2);
			}
        }


		if(Pole[x][y].Checked)
		{
			Image1->Canvas->Draw(x*50,y*50, FlagPc);

		}
		else
		{
			if(Pole[x][y].Mined && Pole[x][y].Opened)
			{
				Image1->Canvas->Draw(x*50,y*50, BombPc);
			}
			else
			{
				if(Pole[x][y].KolBomb>0 &&  Pole[x][y].Opened)
				{
					Image1->Canvas->TextOut(x*50+16,y*50+13,IntToStr(Pole[x][y].KolBomb));
				}

			}
		}
}

void __fastcall TForm1::MakeRandomBombs()
{
	srand(time(NULL));
	int t = 0;
	while(t < BombVsego)
	{
		int xr = rand() % KolKl;
		int yr = rand() % KolKl;
		if(Pole[xr][yr].Mined == False)
		{
			Pole[xr][yr].Mined = True;

			t++;
		}
	}
	CountBombs();
}

void __fastcall TForm1::CountBombs()
{

   for(int i = 0; i < KolKl;i++)
	{
		for(int j = 0; j < KolKl; j++)
		{
			Pole[i][j].KolBomb = 0;
			if(i > 0 && j > 0)
				if(Pole[i - 1][j - 1].Mined == True) Pole[i][j].KolBomb++;
			if(i > 0)
			{
				if(Pole[i - 1][j].Mined == True) Pole[i][j].KolBomb++;
				if(Pole[i - 1][j + 1].Mined == True) Pole[i][j].KolBomb++;
			}
			if(Pole[i][j + 1].Mined == True) Pole[i][j].KolBomb++;
			if(Pole[i + 1][j + 1].Mined == True) Pole[i][j].KolBomb++;
			if(Pole[i + 1][j].Mined == True) Pole[i][j].KolBomb++;
			if(j > 0)
			{
				if(Pole[i + 1][j - 1].Mined == True) Pole[i][j].KolBomb++;
				if(Pole[i][j - 1].Mined == True) Pole[i][j].KolBomb++;
			}

		}

	}
}
void __fastcall TForm1::Check(int x, int y)
{
		if((x>KolKl-1)||(x<0)||(y>KolKl-1)||(y<0))return;
		if(!Pole[x][y].Opened)
		{
			Pole[x][y].Opened=true;
			DrawCletka(x, y);
			if(Pole[x][y].KolBomb==0)
			{
				Check(x+1,y);
				Check(x-1,y);
				Check(x,y+1);
				Check(x,y-1);

				Check(x+1,y+1);
				Check(x-1,y-1);
				Check(x-1,y+1);
				Check(x+1,y-1);
			}
		}
}

void __fastcall TForm1::FormCreate(TObject *Sender)
{
	Image2->Picture->LoadFromFile("clock.bmp");
	Image3->Picture->LoadFromFile("Bomb.bmp");
	Image4->Picture->LoadFromFile("Flag.bmp");
	BombPc=new Graphics::TBitmap();
	FlagPc=new Graphics::TBitmap();
	FlagPc->LoadFromFile("Flag.bmp");
	FlagPc->Transparent=true;
	BombPc->LoadFromFile("Bomb.bmp");
	BombPc->Transparent=true;
	cl1->LoadFromFile("cletka1.bmp");
	//cl1->Transparent=true;
	cl2->LoadFromFile("cletka2.bmp");
	//cl2->Transparent=true;
	cl3->LoadFromFile("cletka3.bmp");
	//cl1->Transparent=true;
	cl4->LoadFromFile("cletka4.bmp");
	//cl2->Transparent=true;
	Image1->Canvas->Font->Size=13;
	Image1->Canvas->Font->Color=clGreen;
	New();
	MakeRandomBombs();

}
//---------------------------------------------------------------------------
void __fastcall TForm1::DrawAll()
{
	for(int i = 0; i < KolKl; i++)
	{
		for(int j = 0; j < KolKl; j++)
		{
			Pole[i][j].Opened = True;
			DrawCletka(i, j);
		}
	}
}


void __fastcall TForm1::Image1MouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y)
{
	Timer1->Enabled=True;
	Edit1->ReadOnly=True;
	int XPos=X/50;
	int YPos=Y/50;
	if(Button==mbLeft)
			{
				if(Pole[XPos][YPos].KolBomb==0)
				{
					Check(XPos,YPos);
				}
				Pole[XPos][YPos].Opened=true;
				DrawCletka(XPos,YPos);
				if(Pole[XPos][YPos].Mined)
				{
					Timer1->Enabled=False;
					DrawAll();
					ShowMessage("Вы проиграли(((((");
					New();
					MakeRandomBombs();
					Panel1->Caption = "00:00";
					Edit1->ReadOnly=False;
                    Edit2->Text = IntToStr(BombVsego);
				}
			}
	if(Button==mbRight)
			{
				if(!Pole[XPos][YPos].Opened)
				{
					if(Pole[XPos][YPos].Checked)
							{
								Pole[XPos][YPos].Checked=false;
								BombLeft++;
								Edit2->Text = IntToStr(BombLeft);
							}
							else
							{
								Pole[XPos][YPos].Checked=true;
								Pole[XPos][YPos].Opened = False;
								BombLeft--;
								Edit2->Text = IntToStr(BombLeft);
							}
					DrawCletka(XPos,YPos);
				}
		}
	if(CheckWin())
			{
				Timer1->Enabled=False;
				ShowMessage("Вы победили!!!!!!");
				New();
				MakeRandomBombs();
				Panel1->Caption = "00:00";
				Edit1->ReadOnly=False;
				Edit2->Text = IntToStr(BombVsego);
			}

}

void __fastcall TForm1::New()
{
   for(int j=0;j<KolKl;j++)
		for(int i=0;i<KolKl;i++)
				{
				Pole[i][j].Opened=false;
				Pole[i][j].KolBomb=0;
				Pole[i][j].Checked=false;
				Pole[i][j].Mined=false;
				}
   BombLeft = BombVsego;
   for(int i = 0; i < KolKl; i++)
	{
		for(int j = 0; j < KolKl; j++)
		{
			if((i + j) % 2 == 0)
			{
				Image1->Canvas->Draw(i*50,j*50,cl1);
			}
			else
			{
				Image1->Canvas->Draw(i*50,j*50,cl2);
			}
		}
	}

}
bool __fastcall TForm1::CheckWin()
{
   for(int j=0;j<KolKl;j++)
			for(int i=0;i<KolKl;i++)
					{
						if((Pole[i][j].Mined)&&(!Pole[i][j].Checked))
							return false;
					}
	return true;
}

//---------------------------------------------------------------------------

void __fastcall TForm1::Timer1Timer(TObject *Sender)
{
	 sec++;
	 if (sec >= 60)
	 {
		sec = 0;
		min++;
	 }
	 String smin, ssec;
	 if(min >= 10)
		smin = IntToStr(min);
	 else
		smin = "0" + IntToStr(min);
	 if(sec >= 10)
		ssec = IntToStr(sec);
	 else
		ssec = "0" + IntToStr(sec);
	 Panel1->Caption = smin + ":" + ssec;
}
//---------------------------------------------------------------------------


void __fastcall TForm1::Edit1Change(TObject *Sender)
{
	BombVsego = StrToInt(Edit1->Text);
	BombLeft = BombVsego;
	Edit2->Text = IntToStr(BombVsego);
    New();
	MakeRandomBombs();
}
//---------------------------------------------------------------------------

