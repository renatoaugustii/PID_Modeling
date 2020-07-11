/*
   POJETO DE MODELAGEM DE PID
   
   Author: Eng. Renato Augusto
    
   OBJETIVO: O objetivo da construção desse projeto se deve ao desafio de modelar e projetar um controlador PID utilizando recursos de uma placa 8 bits (Arduino).
   
   Este programa não substitui um controlador PID e nem possui esse objetivo, os resultados obtidos serão usados posteriormente para fins de cálculos dos parametros de controle.
   Todo o programa se encontra em "Malha Aberta", modo manual dos controladores PID tradicionais.

   Alguma siglas serão adotadas e seus significados estão diretamente relacionadas ao uso comum em matérias de controles industrais.

   MV = Variável manipulada ou saída do controlador.
   PV = Variável do processo
   SP = SetPoint, valor desejado para a variável de processo.

   **************************************************************************************************************************************************************************************
   *                                                                                  IMPORTANTE 
   **************************************************************************************************************************************************************************************
   *  É POSSÍVEL UTILIZAR ESSE PROGRAMA COM QUALQUER GRANDEZA FÍSICA, SEJA ELA, TEMPERATURA, VAZÃO, NÍVEL, PRESSÃO, VELOCIDADE .... DESDE QUE SEJA TOMADO OS CUIDADOS PARA AS TRATATIVAS
   *  DE ENTRADAS PARA A PV. ATENTAR AO USO DAS BIBLIOTECAS FUNDAMENTAIS PARA QUE NÃO SE TENHA NENHUM PROBLEMA AO UTILIZAR O PROGRAMA.
   **************************************************************************************************************************************************************************************
   
   Este projeto é livre e poderá ser melhorado e modificado conforme necessidade do usuário, desde que seja comentado quem foi o criador do arquivo, assim como o seu link de origem.

   Todo o esquemático, fotos e desenhos estão disponíveis na página do Github abaixo.
   
   Github: https://github.com/renatoaugustii

   Atribuição-NãoComercial -  Sujeito a punições legais

   **  CONTROLE DE VERSÕES **
   Versão: 1.0 - Por Renato Augusto
   Data: 11/07/2020
   Belo Horizonte - MG / Brasil 
   
   (Se realizar alguma modificação no projeto identifique o número da versão acima)
   
   Qualquer dúvida ou sujestão entre em contato:
   renato.augusto.correa@outlook.com
   
*/

/** ESCOBO DE INICIALIZAÇÃO DE VARIÁVEIS **/

const int analogPin = 0; // Entrada Analógica que será usado para gerar valores da PV
const int MV_Out = 8; // Define saída física para controle proporcional em PWM.

/** INICIALIZAÇÃO DA VARIÁVEIS -  EDITAR CONFORME NECESSIDADE **/
float PV = 0; // Inicia variavel da PV em Zero
float MV = 50; //Iniciar Variável de controle em 50
int Ta = 1000; // Tempo de amostragem, para geração do gráfico


void setup() {
  
  pinMode(analogPin, INPUT); // Define pino de analogica como entrada física
  pinMode(MV_Out,OUTPUT); // Define saída física
  Serial.begin(9600); // Taxa de comunicação padrão baud rate
}

void loop() {
/************************
 *       ATENÇÃO        *
 *  NO MONITOR SERIAL DIGITE A LETRA 'O' SEM ASPAS E O VALOR DESEJADO PARA A MV, CONFORME O EXEMPLO:     
 *  
 *  EXEMPLO: O35 (COLOCA A MV EM 35%)
 ************************/

  if (Serial.available()>0)
  { 
    char reading  = Serial.read();
        switch(reading)
        {
            case 'o': //change MV_manual
              reading = Serial.parseFloat();
              MV = reading;
              Serial.println(MV);
            break;
        }
   }
   

  if (MV>100){MV=100;} // Interlock upper value
  if (MV<0){MV=0;} // Interlock lower value

  /*** PRINT USING PLOTTER OR MONITOR SERIAL ***/
  Serial.print(PV);
  Serial.print(" ");
  Serial.println(MV);

  /********** CONVERT MV TO PWM *****************/
  analogWrite(MV_Out,map(MV,0,100,0,255));
  //delay(Ta*1);
}
