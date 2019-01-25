//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Grids.hpp>
#include <ComCtrls.hpp>
#include <TabNotBk.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
#include <Chart.hpp>
#include <Series.hpp>
#include <TeEngine.hpp>
#include <TeeProcs.hpp>
#include <Dialogs.hpp>
#include <ExtDlgs.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// Composants gérés par l'EDI
        TTabbedNotebook *TabbedNotebook1;
        TPanel *Panel1;
        TLabel *Label1;
        TImage *Image1;
        TImage *Image2;
        TButton *Button1;
        TButton *Button2;
        TEdit *Edit1;
        TLabel *Label2;
        TButton *Button3;
        TRadioButton *RadioButton1;
        TRadioButton *RadioButton2;
        TRadioButton *RadioButton3;
        TLabel *Label3;
        TChart *Chart1;
        TChart *Chart2;
        TLineSeries *Series1;
        TLineSeries *Series2;
        TLineSeries *Series3;
        TLineSeries *Series4;
        TButton *Button4;
        TButton *Button5;
        TButton *Button6;
        TButton *Button7;
        TLabel *Label4;
        TLabel *Label5;
        TEdit *Edit2;
        TEdit *Edit3;
        TButton *Button8;
        TRadioButton *RadioButton4;
        TRadioButton *RadioButton5;
        TRadioButton *RadioButton6;
        TLabel *Label6;
        TLabel *Label7;
        TEdit *Edit4;
        TButton *Button9;
        TOpenPictureDialog *OpenPictureDialog1;
        TButton *Button10;
        TRadioButton *RadioButton7;
        TLabel *Label8;
        TRadioButton *RadioButton8;
        TButton *Button11;
        void __fastcall Button1Click(TObject *Sender);
        void __fastcall Button2Click(TObject *Sender);
        void __fastcall Button3Click(TObject *Sender);
        void __fastcall RadioButton1Click(TObject *Sender);
        void __fastcall RadioButton2Click(TObject *Sender);
        void __fastcall RadioButton3Click(TObject *Sender);
        void __fastcall Button8Click(TObject *Sender);
        void __fastcall RadioButton4Click(TObject *Sender);
        void __fastcall Button9Click(TObject *Sender);
        void __fastcall RadioButton5Click(TObject *Sender);
        void __fastcall RadioButton6Click(TObject *Sender);
        void __fastcall Button4Click(TObject *Sender);
        void __fastcall Button6Click(TObject *Sender);
        void __fastcall Button5Click(TObject *Sender);
        void __fastcall Button7Click(TObject *Sender);
        void __fastcall Button10Click(TObject *Sender);
        void __fastcall RadioButton8Click(TObject *Sender);
        void __fastcall RadioButton7Click(TObject *Sender);
        void __fastcall Button11Click(TObject *Sender);
private:	// Déclarations de l'utilisateur
public:		// Déclarations de l'utilisateur
        __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
