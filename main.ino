int tempo;//Variavel que armazena o tempo.

void setup()
{
	Serial.begin(115200);//Inicia a comunicaçao serial
	pinMode(2, OUTPUT);//Define o led Onboard como saída


	Serial.printf("\nsetup() em core: %d", xPortGetCoreID());//Mostra no monitor em qual core o setup() foi chamado
	xTaskCreatePinnedToCore(loop2, "loop2", 8192, NULL, 1, NULL, 0);//Cria a tarefa "loop2()" com prioridade 1, atribuída ao core 0
	delay(1);
}

void loop()//O loop() sempre será atribuído ao core 1 automaticamente pelo sistema, com prioridade 1
{
	Serial.printf("\n Tempo corrido: %d", tempo++);
	delay(1000);//Mantem o processador 1 em estado ocioso por 1seg
}

void loop2(void*z)//Atribuímos o loop2 ao core 0, com prioridade 1
{
	Serial.printf("\nloop2() em core: %d", xPortGetCoreID());//Mostra no monitor em qual core o loop2() foi chamado
	while (1)//Pisca o led infinitamente
	{
		digitalWrite(2, !digitalRead(2));
		delay(100);
	}
}
