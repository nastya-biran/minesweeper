//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TImage *Image1;
	TImage *Image2;
	TPanel *Panel1;
	TTimer *Timer1;
	TImage *Image3;
	TImage *Image4;
	TEdit *Edit1;
	TEdit *Edit2;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall DrawCletka(int x, int y);
	void __fastcall DrawAll();
	void __fastcall New();
	void __fastcall MakeRandomBombs();
	void __fastcall CountBombs();
    bool __fastcall CheckWin();
	void __fastcall Check(int x, int y);
	void __fastcall Image1MouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall Timer1Timer(TObject *Sender);
	void __fastcall Edit1Change(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
