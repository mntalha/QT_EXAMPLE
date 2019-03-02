#ifndef PRINTER_H
#define PRINTER_H
#include "serial.h"
#include <QDebug>
#include <QCoreApplication>

class Printer : public QObject
{
   Q_OBJECT
public:
     Printer();
     serialport *myserial;
     QByteArray RxData;
     enum QR {
         /*
        QRCODE OR MICROQR CHOOSE AS PREFER
        */
         QRcode=0,
         MicroQR=1
     };
     enum QR_Version{
          /*
         ıt stands for the version number.
         As a default auto version is selected.
         */
             Auto=0,
             V1=1,
             V2=2,
             V3=3,
             V4=4,
             V5=5,
             V6=6,
             V7=7,
             V8=8,
             V9=9,
             V10=10,
             V11=11,
             V12=12,
             V13=13,
             V14=14,
             V15=15,
             V16=16,
             V17=17,
             V18=18,
             V19=19,
             V20=20,
             V21=21,
             V22=22,
             V23=23,
             V24=24,
             V25=25,
             V26=26,
             V27=27,
             V28=28,
             V29=29,
             V30=30,
             V31=31,
             V32=32,
             V33=33,
             V34=34,
             V35=35,
             V36=36,
             V37=37,
             V38=38,
             V39=39,
             V40=40

         };
     enum QR_error_correction
         {
          /*
          ıt provide the restore data when qrcode is damaged.
          There are 4 level in this mode
             LEVEL L  APPROX %7
             LEVEL M  APPROX %15
             LEVEL Q  APPROX %25
             LEVEL H  APPROX %30
         */
             AUTO=0,
             L_LEVEL=1,
             M_LEVEL=2,
             Q_LEVEL=3,
             H_LEVEL=4

         };
     enum Double_Strike{

        Double_Strike_Off=0,
        Double_Strike_On=1
      };
     enum Underline_Mode{
          UNDERLINE_MODE_OFF=0,
          ONE_DOT_THICKNESS=1,
          TWO_DOT_THICKNESS=2
      };
     enum Italic_Mode{

          ITALIC_MODE_OFF=0,
          ITALIC_MODE_ON=1
      };
     enum Font_Size{
          FONT_12_CPI,
          FONT_16_CPI,
          FONT_22_CPI
      };
     enum Character_Width_Size{
          NORMAL_WIDTH_SIZE=0,
          TWO_TIMES_WIDTH=0x10,
          THREE_TIMES_WIDTH=0x20,
          FOUR_TIMES_WIDTH=0x30,
          FIVE_TIMES_WIDTH=0x40,
          SIX_TIMES_WIDTH=0x50,
          SEVEN_TIMES_WIDTH=0x60,
          EIGHT_TIMES_WIDTH=0x70
      };
     enum Character_Height_Size{
          NORMAL_HEIGHT_SIZE=0,
          TWO_TIMES_HEIGHT=0x01,
          THREE_TIMES_HEIGHT=0x02,
          FOUR_TIMES_HEIGHT=0x03,
          FIVE_TIMES_HEIGHT=0x04,
          SIX_TIMES_HEIGHT=0x05,
          SEVEN_TIMES_HEIGHT=0x06,
          EIGHT_TIMES_HEIGHT=0x07
      };
     enum Line_Spacing{
          ONE_OVER_SIX_INCH,
          ONE_OVER_EIGHT_INCH
      };
     enum Select_Justification{
                FLUSH_LEFT,
                FLUSH_CENTER,
                FLUSH_RIGHT

     };
     void init();
     void receipt_print_line(QByteArray name,QByteArray rate,QByteArray price);
     void print_header_line(QByteArray line);
     void print_info_line(QByteArray line);
     void print_current_date_time();
     void print_receipt_no(QByteArray no);
     void print_dots();
     void print_comment(QByteArray line);
     void print_total_kdv_value(QByteArray name,QByteArray value);
     void print_z_eku_value(QByteArray z_value,QByteArray eku_value);
     void print_pump_tab_value(QByteArray pump_value,QByteArray tab_value);
     void print_licence_plate(QByteArray plate);
      /* CHARACTER COMMAND FUNCTIONS-------------------------------------------------------------------------------------------*/
      void double_strike_mode(Double_Strike mode);
      void turn_underline_mode(Underline_Mode mode);
      void turn_italic_mode(Italic_Mode mode);
      void set_font_size(Font_Size size);
      void set_width_character_size(Character_Width_Size width);
      void set_height_character_size(Character_Height_Size height);
      /* ------------------------------------------------------------------------------------------------------------*/


      /* PRINT POSITION FUNCTIONS-------------------------------------------------------------------------------------------*/
      void back_space();
      void horizontal_tab();
      void paper_feed(int number);
      void set_justification(Select_Justification type);
      /* ------------------------------------------------------------------------------------------------------------*/


      /* LINE SPACING FUNCTION-------------------------------------------------------------------------------------------*/
      void set_line_spacing(Line_Spacing amount);
      /* ------------------------------------------------------------------------------------------------------------*/


       /* QR CODE FUNCTIONS-------------------------------------------------------------------------------------------*/
      void encoding_scheme_of_QRcode(QR code);
      void spesify_dot_size_of_QRcode(int dotsize);
      void specify_qrcode_version(QR_Version version);
      void specify_qrcode_error_correction_level(QR_error_correction error_level);
      void store_qrcode_data(QByteArray word);
      void print_qrcode();
      /* ------------------------------------------------------------------------------------------------------------*/


      /* WRITE AND READ DATA  FUNCTIONS-------------------------------------------------------------------------------------------*/
      void write(QByteArray &data);
      void read(QByteArray &RxData);
      /* ------------------------------------------------------------------------------------------------------------*/

};
#endif // PRINTER_H
