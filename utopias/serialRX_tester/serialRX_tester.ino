char cad[100];
int pos = 0;
void setup()
{
  lcd.begin(16, 2);
  lcd.setCursor(1, 0);
  vw_setup(2000);
  vw_rx_start();
}
void loop()
{
  byte buf[VW_MAX_MESSAGE_LEN];
  byte buflen = VW_MAX_MESSAGE_LEN;
  int i;
  if ( vw_get_message(buf, &buflen) )
  {
    if (pos < 2)
      lcd.setCursor(0, pos);
    else
    {
      pos = 0;
      lcd.clear();
    }
    for (i = 1; i < buflen; i++)
    {
      lcd.print((char)buf[i]);
      pos++;

    }
  }
}
