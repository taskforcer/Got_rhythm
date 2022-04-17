

#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978

int Pin_zufall = A6;
int Pin_wachbleiben = A4;
int Pin_LED = 8;
int Pin_piezo = 6;
int Pin_mikrofon = 12;
int Pin_hbruecke1 = 7;   // Ist immer so
int Pin_hbruecke2 = 6;   // Ist immer so
int Pin_enable12 = A0;

int Pin_hbruecke3 = 3;   // Ist immer so, aber Lücke mit Draht überbruecken!
int Pin_hbruecke4 = 4;   // Ist immer so, aber Lücke mit Draht überbruecken!

/*#############################################################################*/
/* in der Struktur "rhythmus" werden die Schläge und die Kontrollbereiche definiert, 
 * die zu einem Schlagrythmus gehören. 
 * 
 * Es sollen jeweils 3 Takte gefüllt werden. Die Taktlänge ist jeweils 500. 
 * EinRhythmus muss imm auf Zeil 0 anfangen. 
 */
#define MAX_BEATS 12            // Die Maximale Anzahl von Schlägen, die zu einem Rythmus gehören
struct rhythmus
{
  int anz_beats; 
  int beats[MAX_BEATS];         // Definition der Position des Schlages
  int vorher[MAX_BEATS];        // Gibt an, wieviele Einheiten der über das Mikrofon detektierte 
                                // Nachahmerschlag früher liegen darf. 
  int nachher[MAX_BEATS];       // Gibt an, wieviele Einheiten der über das Mikrofon detektierte 
                                // Nachahmerschlag später liegen darf.                            
};


rhythmus Startrhythmus =
{     // Drei gleichmäßige Schläge
  3,
  {0, 500, 2000, 0, 0, 0, 0, 0, 0, 0, 0},  // Lage der Beats
  {-300, -300, -300, 0, 0, 0, 0, 0, 0, 0, 0, 0},// Toleranz nach früh
  {300, 300, 300, 0, 0, 0, 0, 0, 0, 0, 0, 0}    // Toleranz nach spät
};

rhythmus Rhythmus2
{     // vier Schläge
  4,
  {0, 500, 500, 2000, 0, 0, 0, 0, 0, 0, 0, 0}, // Lage der Beats
  {-200, -200, -200, -300, 0, 0, 0, 0, 0, 0, 0, 0},// Toleranz nach früh
  {200, 200, 200, 300, 0, 0, 0, 0, 0, 0, 0, 0}       // Toleranz nach spät
};

rhythmus Rhythmus3
{     // vier Schläge
  4,
  {0, 500, 1500, 2000, 0, 0, 0, 0, 0, 0, 0, 0}, // Lage der Beats
  {-200, -200, -200, -300, 0, 0, 0, 0, 0, 0, 0, 0},// Toleranz nach früh
  {200, 200, 200, 300, 0, 0, 0, 0, 0, 0, 0, 0}     // Toleranz nach spät
};

rhythmus Rhythmus4
{     // vier Schläge
  4,
  {0, 500, 500, 1500, 0, 0, 0, 0, 0, 0, 0, 0}, // Lage der Beats
  {-200, -200, -200, -200, 0, 0, 0, 0, 0, 0, 0, 0},// Toleranz nach früh
  {200, 200, 200, 200, 0, 0, 0, 0, 0, 0, 0, 0}     // Toleranz nach spät
};



#define MAX_RHYTHMEN 7          // Die maximale Anzahl von Schlagrhythmen im Array
rhythmus R_array[ MAX_RHYTHMEN ] =
{

{     // Drei gleichmäßige Schläge
  3,
  {0, 1000, 2000, 0, 0, 0, 0, 0, 0, 0, 0},  // Lage der Beats
  {-300, -300, -300, 0, 0, 0, 0, 0, 0, 0, 0, 0},// Toleranz nach früh
  {300, 300, 300, 0, 0, 0, 0, 0, 0, 0}    // Toleranz nach spät
},

{     // vier Schläge
  4,
  {0, 500, 1000, 2000, 0, 0, 0, 0, 0, 0, 0, 0}, // Lage der Beats
  {-200, -300, -300, -300, 0, 0, 0, 0, 0, 0, 0, 0},// Toleranz nach früh Kommentar dazu!
  {200, 300, 300, 300, 0, 0, 0, 0, 0, 0, 0, 0}       // Toleranz nach spät
},

{     // vier Schläge
  4,
  {0, 750, 1000, 2000, 0, 0, 0, 0, 0, 0, 0, 0}, // Lage der Beats
  {-200, -200, -300, -300, 0, 0, 0, 0, 0, 0, 0, 0},// Toleranz nach früh
  {200, 200, 300, 300, 0, 0, 0, 0, 0, 0, 0, 0}     // Toleranz nach spät
},

{     // vier Schläge
  4,
  {0, 333, 666, 1500, 0, 0, 0, 0, 0, 0, 0, 0}, // Lage der Beats
  {-200, -200, -200, -300, 0, 0, 0, 0, 0, 0, 0, 0},// Toleranz nach früh
  {200, 200, 200, 300, 0, 0, 0, 0, 0, 0, 0, 0}     // Toleranz nach spät
},

{     // acht Schläge
  8,
  {0, 250, 1000, 1250, 2000, 2250, 3000, 3250, 0, 0, 0, 0}, // Lage der Beats
  {-200, -200, -200, -300, -300, -300, -300, -300, 0, 0, 0, 0},// Toleranz nach früh
  {200, 200, 200, 300, 300, 300, 300, 300, 0, 0, 0, 0}     // Toleranz nach spät
},

{     // neun Schläge
  9,
  {0, 1000, 2000, 2250, 2500, 2750, 3000, 4000, 5000, 0, 0, 0}, // Lage der Beats
  {-200, -200, -200, -300, -300, -300, -300, -400, -400, 0, 0, 0},// Toleranz nach früh
  {200, 200, 200, 300, 300, 300, 300, 400, 400, 0, 0, 0}     // Toleranz nach spät
}, 

{     // zwölf Schläge
  12,
  {0, 1000, 2000, 2250, 2500, 2750, 3000, 3250, 3500, 3750, 4000, 5000}, // Lage der Beats
  {-200, -200, -200, -300, -300, -300, -300, -400, -400, -400, -400, -400},// Toleranz nach früh
  {200, 200, 200, 300, 300, 300, 300, 400, 400, 400, 400, 400}     // Toleranz nach spät
}


};



/* Die folgende Funktion spielt einen Rhytmus vor, 
 *  wartet auf das Echo, testet dieses
 *  Wenn das Echo OK ist, wir True zurückgegeben, 
 *  wenn das Echo nicht innerhalb der Zeitgrenzen ist, wird ein zweites Mal getestet
 */
int teste_rhythmus( rhythmus rhyt[] )
{
  unsigned long startzeit;
  int zeit;
  int schlag;
  int bestanden;

  

  // Erstes Vorspielen:
  startzeit = millis();
  schlag = 0;
  for( zeit = -500; (zeit < rhyt->beats[ rhyt->anz_beats -1] +500); )
    {
      zeit = -500 +(millis()-startzeit);

      if( schlag >= rhyt->anz_beats )
        {
          continue;
        }
        
      if( zeit > rhyt->beats[schlag] ) 
        {
          tone( Pin_piezo, 440, 25);
          delay( 25 );
          schlag++;
        }
    }   // ..Ende erstes Vorspielen..

   // Erstes Abprüfen
   startzeit = millis();
   bestanden = true;
   schlag = 0;
   for( zeit = 0; (zeit < rhyt->beats[ rhyt->anz_beats -1] +2000); )
     {
        zeit = (millis()-startzeit);

        if(schlag >= rhyt->anz_beats ) 
          continue;
          
        if( (zeit > (rhyt->beats[schlag] + rhyt->nachher[schlag])) && (schlag > 0 ) )
          {
            schlag++;
            Serial.print( " Zeitverzug:" );
            Serial.println( zeit );
            bestanden = false;
          }
        
        if( digitalRead( Pin_mikrofon ) )
         {  // Ein Nachahmerschlag wurde detektiert: 

            // Der Anfang muss nicht genau getroffen werden. Das ist zu schwiering. 
            // (Dann lieber kompliziertere Schlagmuster!)
            if( schlag == 0 )
              {
                startzeit = millis();
                zeit = 0;
              }
            
            if( (zeit < (rhyt->beats[schlag] + rhyt->vorher[schlag])) && (schlag > 0) )
              {
                bestanden = false;
              }

            digitalWrite( Pin_LED, true );
            delay( 150 );
            digitalWrite( Pin_LED, false );
            delay( 50 );

            if( digitalRead( Pin_mikrofon ) )Serial.println( "Signal zu lange oben!" );
            
            Serial.print( "S: " ); Serial.print( schlag ); 
            Serial.print( " Zeit: " );
            Serial.println( zeit );
            schlag++;
              
         }  // ..ein Nachahmerschlag wurde detektiert..
         
     }    // ..Ende der for-zeitschleife zum ersten Testen des Echo-Rhythmus..

  if( bestanden &&(schlag>0) ) return( true ); 

  // Zweites Vorspielen:
  startzeit = millis();
  bestanden = true;
  schlag = 0;
  for( zeit = -500; (zeit < rhyt->beats[ rhyt->anz_beats -1] +500); )
    {
      zeit = -500 +(millis()-startzeit);

      if( schlag >= rhyt->anz_beats )
        continue;
        
        
      if( zeit > rhyt->beats[schlag] ) 
        {
          tone( Pin_piezo, 440, 25);
          delay( 25 );
          schlag++;
        }
        
    }   // ..Ende for-Schleife zweites Vorspielen..

   // Zweites Abprüfen
   startzeit = millis();
   bestanden = true;
   schlag = 0;
   for( zeit = 0; (zeit < rhyt->beats[ rhyt->anz_beats -1] +2000) ; )
     {
        zeit = (millis()-startzeit);
        
        if(schlag >= rhyt->anz_beats ) 
          continue;
        
        if( (zeit > (rhyt->beats[schlag] + rhyt->nachher[schlag])) && (schlag > 0) )
          {
            schlag++;
            Serial.print(" Verstrichen " );
            Serial.println(zeit);
            bestanden = false;
          }
        
        if( digitalRead( Pin_mikrofon ) )
         {  // Ein Nachahmerschlag wurde detektiert: 

            // Der Anfang muss nicht genau getroffen werden. Das ist zu schwiering. 
            // (Dann lieber kompliziertere Schlagmuster!)
            if( schlag == 0 )
              {
                startzeit = millis();
                zeit = 0;
              }
              
            if( (zeit < (rhyt->beats[schlag] + rhyt->vorher[schlag])) && (schlag > 0) )
              {
                bestanden = false;
              }

            digitalWrite( Pin_LED, true );
            delay( 150 );
            digitalWrite( Pin_LED, false );
            delay( 50 );

            if( digitalRead( Pin_mikrofon ) ) Serial.println( "Signal zu lange oben!" );

            Serial.print( "S: " ); Serial.print( schlag ); 
            Serial.print( " Zeit: " );
            Serial.println( zeit );
            schlag++;
              
         }  // ..ein Nachahmerschlag wurde detektiert..
         
     }    // ..Ende der for-zeitschleife zum ersten Testen des Echo-Rhythmus..
 
  return( bestanden &&(schlag>0) );
  
}  // ..Ende von "teste_rhythmus()"..


void verlierermelodie()
{
  int i;

  for( i=400; i-=40; i>0 )
    {
      tone( Pin_piezo, i, 500);
      delay( 100 );
    }
}


/***********************************************************************
 * Festlegungen für die Siegermelodie:
 **********************************************************************/

// notes in the melody:
int melody[] = {
  NOTE_E4, NOTE_F4, NOTE_G4, NOTE_C5, NOTE_D4, NOTE_E4, NOTE_F4, 
  NOTE_A4, NOTE_B4, NOTE_C5, NOTE_F5, NOTE_A4, NOTE_B4, NOTE_C5, NOTE_D5, NOTE_E5  , 
  NOTE_E4, NOTE_F4, NOTE_G4, NOTE_C5, NOTE_D5, NOTE_E5, NOTE_F5, 
  NOTE_D5, NOTE_E5, NOTE_F5, NOTE_A4, NOTE_A4, NOTE_A4, NOTE_F5, NOTE_A4, NOTE_A4, NOTE_A4,
  NOTE_F5, NOTE_E5, NOTE_D5, NOTE_A4, NOTE_A4, NOTE_A4, NOTE_D5, NOTE_A4, NOTE_A4, NOTE_A4,
  NOTE_E5, NOTE_D5, NOTE_C5
};

// note durations
int noteDurations[] = {
  500*3/4, 500/4, 500, 500*2, 500*3/4, 500/4, 500*3, 
  500*3/4, 500/4, 500, 500*2, 500*3/4, 500/4, 500, 500, 500,
  500*3/4, 500/4, 500, 500*2, 500*3/4, 500/4, 500*3, 
  500*3/4, 500/4, 500, 500/3, 500/3, 500/3, 500, 500/3, 500/3, 500/3,
  500*3/4, 500/4, 500, 500/3, 500/3, 500/3, 500, 500/3, 500/3, 500/3,
  500*3/4, 500/4, 500*2
  
};

void siegermelodie()
{
  // iterate over the notes of the melody:
  for (int thisNote = 0; thisNote < 46; thisNote++) {

   
    int noteDuration =  noteDurations[thisNote];
    tone(Pin_piezo, melody[thisNote], noteDuration);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(Pin_piezo);
  }
}     // ..Ende von "siegermelodie()"..



void LED_an()
{
  digitalWrite( Pin_LED, true );
}

void LED_aus() 
{
  digitalWrite( Pin_LED, false );
}

void bleibe_wach()
{
  analogWrite( Pin_wachbleiben, 0 );
}

void schlafe_ein()
{
  analogWrite( Pin_wachbleiben, 255 );
  delay( 4000 );
}

void motor_links()
{
  analogWrite( Pin_enable12, 255 );
  delay( 10 );
  digitalWrite( Pin_hbruecke1, false );
  digitalWrite( Pin_hbruecke2, true );
}

void motor_rechts()
{
  analogWrite( Pin_enable12, 255 );
  delay( 10 );
  digitalWrite( Pin_hbruecke1, true );
  digitalWrite( Pin_hbruecke2, false );
}

void motor_aus()
{
  digitalWrite( Pin_hbruecke1, true );
  digitalWrite( Pin_hbruecke2, true );
  analogWrite( Pin_enable12, 0 );
  delay( 10 );
}



void setup() 
{
  int i;
  int ok; 
  
  // put your setup code here, to run once:
  pinMode( Pin_hbruecke1, OUTPUT );
  pinMode( Pin_hbruecke2, OUTPUT );
  pinMode( Pin_enable12, OUTPUT );
  motor_aus();

  pinMode( Pin_mikrofon, INPUT );
  pinMode( Pin_wachbleiben, OUTPUT );
  pinMode( Pin_LED, OUTPUT );
  pinMode( Pin_piezo, OUTPUT );
  pinMode( Pin_zufall, INPUT );      // Zur Erzeugung einer Zufallszahl, darf nicht angeschlossen sein!

  randomSeed( analogRead( Pin_zufall ) );
  
  Serial.begin( 9600 );
  
  bleibe_wach();

  
  LED_an();
  delay( 500 );
  LED_aus(); delay( 1000 );
 
   
  
  for( i = 0; i<MAX_RHYTHMEN; i++ )
    {
      ok= teste_rhythmus( R_array + i );
      Serial.print( "Rhythmustest " );Serial.print( i ); 
      if( ok ) 
        Serial.println( ": OK! " );
      else 
        Serial.println( ": N.i.O.!" );
      
      if( !ok )
        {
          verlierermelodie();
          schlafe_ein();  
          
        }
      
    }
  
// Hier Code zum Öffnen des Deckels:
digitalWrite( Pin_LED, true );
motor_rechts(); delay( 3000 );   // Box auf
siegermelodie();


motor_links(); delay( 2000 );    // Box zu
schlafe_ein();  

  
}  // ..Ende von setup()..


void loop() 
{
 
}    // ..Ende von loop()..
