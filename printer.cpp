#include "printer.h"

Printer::Printer()
{
    myserial=new serialport(1);
}

void Printer::double_strike_mode(Printer::Double_Strike mode)
{
    QByteArray data;
    data[0]=0x1B;
    data[1]=0x47;
    data[2]=mode;
    myserial->writeData(data);

}

void Printer::turn_underline_mode(Underline_Mode mode)
{
    QByteArray data;
             data[0]=0x1B;
             data[1]=0x2D;
             data[2]=mode;
   myserial->writeData(data);
}

void Printer::turn_italic_mode(Printer::Italic_Mode mode)
{
    QByteArray data;
             data[0]=0x1B;
             data[1]=0x34;
             data[2]=mode;
   myserial->writeData(data);

}

void Printer::set_font_size(Printer::Font_Size size)
{
    QByteArray data;
             data[0]=0x1B;
             data[1]=0xC1;
             data[2]=0; //
             data[3]=0x1B;
             data[4]=0x4D;
             data[5]=0x31;

    switch(size){
    case FONT_12_CPI:
        data[2]=0x32;
        break;

    case  FONT_16_CPI:
        data[2]=0x30;
        break;
    case  FONT_22_CPI:
        data[2]=0x31;
       break;
    }
    myserial->writeData(data);

}

void Printer::set_height_character_size(Printer::Character_Height_Size height)
{
    QByteArray data1;
             data1[0]=0x1D;
             data1[1]=0x21;
             data1[2]=height;
   myserial->writeData(data1);

}

void Printer::set_line_spacing(Printer::Line_Spacing amount)
{
    QByteArray data;
             data[0]=0x1B;
    switch(amount)
    {
    case ONE_OVER_SIX_INCH:
        data[1]=0x32;
        break;
    case ONE_OVER_EIGHT_INCH:
        data[1]=0x30;
        break;

    }
    myserial->writeData(data);

}

void Printer::set_width_character_size(Printer::Character_Width_Size width)
{
    QByteArray data;
             data[0]=0x1D;
             data[1]=0x21;
             data[2]=width;
    myserial->writeData(data);

}

void Printer::back_space()
{
    /*
    Moves print position to previous character
   */
    QByteArray data;
    data[0]=0x08;
    myserial->writeData(data);

}

void Printer::horizontal_tab()
{
    /*
    Moves the print position to the next horizontal tab position
   */
    QByteArray data;
    data[0]=0x09;
    myserial->writeData(data);

}

void Printer::init()
{
    /*
    Initialization function is made.
   */
    double_strike_mode(Printer::Double_Strike::Double_Strike_Off);
    turn_underline_mode(Printer::Underline_Mode::UNDERLINE_MODE_OFF);
    turn_italic_mode(Printer::Italic_Mode::ITALIC_MODE_OFF);
    set_font_size(Printer::Font_Size::FONT_22_CPI);
    set_width_character_size(Printer::Character_Width_Size::TWO_TIMES_WIDTH);
    set_line_spacing(Printer::Line_Spacing::ONE_OVER_SIX_INCH);
    set_justification(Printer::Select_Justification::FLUSH_LEFT);

}

void Printer::receipt_print_line(QByteArray name, QByteArray rate, QByteArray price)
{
    /*
     |12 Character name|3 Character rate|6 Character price|
      ----------------        %--           *-----
   */

    QByteArray space;
    space=" ";
    QByteArray print;
    print[0]=0x0A;
    int name_size=10;
    int price_size=8;
    int name_lenght=name.length();
    int price_lenght=price.length();

    for(int i=0;i<name_size-name_lenght;i++)
    {
        name.append(space);
    }

    switch(rate.length())
    {
     case 1:
        rate.prepend("%");
        rate.append(space);
        break;
     case 2:
        rate.prepend("%");
        break;
    }
    price.prepend("*");
    for(int i=1;i<price_size-price_lenght;i++)
    {
    price.prepend(space);
    }

    myserial->writeData(name);
    myserial->writeData(rate);
    myserial->writeData(price);
    myserial->writeData(print);
}

void Printer::print_header_line(QByteArray line)
{
    /*
    Set in the middle the line
   */
    double_strike_mode(Printer::Double_Strike::Double_Strike_On);
    QByteArray space;
       space=" ";
    QByteArray print;
       print[0]=0x0A;
    int line_size=21;
    int space_size=(line_size-line.length())/2;
    //qDebug()<<space_size;
    for(int i=0;i<space_size;i++)
    {
        line.prepend(space);
    }
    myserial->writeData(line);
    myserial->writeData(print);
    double_strike_mode(Printer::Double_Strike::Double_Strike_Off);

}

void Printer::print_info_line(QByteArray line)
{
    /*
    Set in the middle the info line
   */
    QByteArray space;
       space=" ";
    QByteArray print;
       print[0]=0x0A;
  int line_size=21;
  int space_size=(line_size-line.length())/2;
 // qDebug()<<space_size;
  for(int i=0;i<space_size;i++)
    {
      line.prepend(space);
    }
   myserial->writeData(line);
   myserial->writeData(print);

}

void Printer::print_current_date_time()
{
    /*
    Print the current date and time
    */
 QByteArray print;
 print[0]=0x0A;
 QString stringDate=QDateTime::currentDateTime().toString("dd.MM.yyyy");
 QString stringTime;
 stringTime=" SAAT:";
 stringTime.append(QDateTime::currentDateTime().toString("HH:mm"));
 QByteArray date=stringDate.toUtf8();
 QByteArray time=stringTime.toUtf8();
 myserial->writeData(date);
 myserial->writeData(time);
 myserial->writeData(print);
}

void Printer::print_receipt_no(QByteArray no)
{
    /*
    Print the receipt no
   */
    QByteArray print;
    print[0]=0x0A;
    QByteArray word;
    word="FIS NO: ";
    word.append(no);
    myserial->writeData(word);
    myserial->writeData(print);
}

void Printer::print_dots()
{
    /*
    print the dots like "-------------------"
   */
    QByteArray print;
    print[0]=0x0A;
    QByteArray dots;
    for(int i=0;i<21;i++){
        dots.append("-");
    }
    double_strike_mode(Printer::Double_Strike::Double_Strike_On);

    myserial->writeData(dots);
    myserial->writeData(print);

    double_strike_mode(Printer::Double_Strike::Double_Strike_Off);

}

void Printer::print_comment(QByteArray line)
{
    /*
    Set in the middle the comment line
   */
    QByteArray space;
       space=" ";
    QByteArray print;
       print[0]=0x0A;
  int line_size=21;
  int space_size=(line_size-line.length())/2;
  //qDebug()<<space_size;
  for(int i=0;i<space_size;i++)
    {
      line.prepend(space);
    }
   myserial->writeData(line);
   myserial->writeData(print);
}

void Printer::print_total_kdv_value(QByteArray name, QByteArray value)
{
    int name_size=7;
    int value_size=5;
    int name_lenght=name.length();
    int value_lenght=value.length();
    QByteArray space;
       space=" ";
    for(int i=0;i<name_size-name_lenght;i++)
    {
        name.append(space);
    }

    for(int i=0;i<value_size-value_lenght;i++)
    {
    value.prepend(space);
    }
    value.append("TL");
    set_width_character_size(Printer::Character_Width_Size::THREE_TIMES_WIDTH);
    myserial->writeData(name);
    myserial->writeData(value);
    set_width_character_size(Printer::Character_Width_Size::TWO_TIMES_WIDTH);
    QByteArray print;
    print[0]=0x0A;
    myserial->writeData(print);

}

void Printer::print_z_eku_value(QByteArray z_value, QByteArray eku_value)
{
    int z_size=5;
    int eku_size=4;
    int z_lenght=z_value.length();
    int eku_lenght=eku_value.length();
    QByteArray space;
       space=" ";
    for(int i=0;i<z_size-z_lenght;i++)
    {
        z_value.append(space);
    }
    z_value.prepend("Z NO:");
    eku_value.prepend("EKU NO:");
    for(int i=0;i<eku_size-eku_lenght;i++)
    {
    eku_value.prepend(space);
    }

    myserial->writeData(z_value);
    myserial->writeData(eku_value);
    QByteArray print;
    print[0]=0x0A;
    myserial->writeData(print);

}

void Printer::print_pump_tab_value(QByteArray pump_value, QByteArray tab_value)
{
    int pump_size=3;
    int tab_size=2;
    int pumb_value_lenght=pump_value.length();
    int tab_value_lenght=tab_value.length();
    QByteArray space;
       space=" ";
    for(int i=0;i<pump_size-pumb_value_lenght;i++)
    {
        pump_value.append(space);
    }
    pump_value.prepend("POMPA NO:");
    tab_value.prepend("TAB NO:");

    for(int i=0;i<tab_size-tab_value_lenght;i++)
    {
    tab_value.prepend(space);
    }

    myserial->writeData(pump_value);
    myserial->writeData(tab_value);
    QByteArray print;
    print[0]=0x0A;
    myserial->writeData(print);
}

void Printer::print_licence_plate(QByteArray plate)
{
    set_width_character_size(Printer::Character_Width_Size::THREE_TIMES_WIDTH);
    set_justification(Printer::Select_Justification::FLUSH_CENTER);
    myserial->writeData(plate);
    QByteArray print;
    print[0]=0x0A;
    myserial->writeData(print);
    set_width_character_size(Printer::Character_Width_Size::TWO_TIMES_WIDTH);
    set_justification(Printer::Select_Justification::FLUSH_LEFT);

}


void Printer::paper_feed(int number)
{
    /*
    Print the number of feed
   */
    QByteArray data;
    data[0]=0x1B;
    data[1]=0x64;
    data[2]=number;
    myserial->writeData(data);

}

void Printer::set_justification(Printer::Select_Justification type)
{
    QByteArray data;
            data[0]=0x1B;
            data[1]=0x61;
    switch(type)
    {
    case FLUSH_LEFT:
        data[2]=0x30;
        break;
    case FLUSH_CENTER:
        data[2]=0x31;
        break;
     case FLUSH_RIGHT:
        data[2]=0x32;
        break;

    }
    myserial->writeData(data);

}

void Printer::encoding_scheme_of_QRcode(Printer::QR code)
{
    QByteArray data;
    data[0]=0x1D;
    data[1]=0x28;
    data[2]=0x6B;
    data[3]=0x03;
    data[4]=0x00;
    data[5]=49;
    data[6]=65;
    data[7]=code;
    myserial->writeData(data);
    qDebug()<<code<<"is selected";
}

void Printer::spesify_dot_size_of_QRcode(int dotsize)
{
    QByteArray data;
    data[0]=0x1D;
    data[1]=0x28;
    data[2]=0x6B;
    data[3]=0x03;
    data[4]=0x00;
    data[5]=49;
    data[6]=66;
    data[7]=dotsize;
    myserial->writeData(data);
    qDebug()<<dotsize<<"dotsize is selected";
}

void Printer::specify_qrcode_version(Printer::QR_Version version)
{
    QByteArray data;
    data[0]=0x1D;
    data[1]=0x28;
    data[2]=0x6B;
    data[3]=0x03;
    data[4]=0x00;
    data[5]=49;
    data[6]=67;
    data[7]=version;
    myserial->writeData(data);
    qDebug()<< version <<". version is selected";
}

void Printer::specify_qrcode_error_correction_level(Printer::QR_error_correction error_level)
{
    QByteArray data;
    data[0]=0x1D;
    data[1]=0x28;
    data[2]=0x6B;
    data[3]=0x03;
    data[4]=0x00;
    data[5]=49;
    data[6]=69;
    data[7]=error_level;
    myserial->writeData(data);
    qDebug()<<error_level<<". level is selected";
}

void Printer::store_qrcode_data(QByteArray word)
{
    int word_lenght=word.length()+3;
    QByteArray data;
    data[0]=0x1D;
    data[1]=0x28;
    data[2]=0x6B;
    data[3]=word_lenght;
    data[4]=0x00;
    data[5]=49;
    data[6]=80;
    data[7]=49;
    data.append(word);
    myserial->writeData(data);
    qDebug()<<"DATA IS STORED";
}

void Printer::print_qrcode(){

    QByteArray data;
    data[0]=0x1D;
    data[1]=0x28;
    data[2]=0x6B;
    data[3]=0x03;
    data[4]=0x00;
    data[5]=49;
    data[6]=81;
    data[7]=49;
    myserial->writeData(data);
    qDebug()<<"QR CODE PRINTED";
}

void Printer::write(QByteArray &data)
{
    myserial->writeData(data);
}

void Printer::read(QByteArray &RxData)
{
    myserial->readData(RxData);

}
