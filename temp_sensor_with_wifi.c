#include <reg51.h>

int a=0,i,k,j,n=0;
char temp;
unsigned char y,num[4]={'0','0','0','\0'};

void convert(unsigned int z);
void tx_str(unsigned char *disp);
unsigned char rx_char();
void tx_char(unsigned char v1);
void delay(int x);
void at_cmd();

void main ()
{
	TMOD=0x20;
	TH1=0xfd;
	SCON=0x50;
	TR1=1;
	TI=0;
	
	while(rx_char()!='I');
	while(rx_char()!='P');
	
	tx_str("AT");
	tx_char(0x0D);
	tx_char(0x0A);
	
	while(rx_char()!='O');
	while(rx_char()!='K');
	
	tx_str("AT+CIPMUX=0");
	tx_char(0x0D);
	tx_char(0x0A);
	
	while(rx_char()!='O');
	while(rx_char()!='K');
	
	delay(200);
	tx_str("AT+CWMODE=1");
	tx_char(0x0D);
	tx_char(0x0A);
	
	while(rx_char()!='O');
	while(rx_char()!='K');
	
	delay(200);
	tx_str("AT+CWJAP=\"mriic_IOT\",\"mriic_iot\"");
	tx_char(0x0D);
	tx_char(0x0A);
	
	while(rx_char()!='O');
	while(rx_char()!='K');
	
	delay(200);
	while(1)
	{
		n=n+4;
		convert(n);
		at_cmd();
		delay(500);
	}	
}

void at_cmd()
{
	tx_str("AT+CIPSTART=\"TCP\",\"192.168.50.3\",80");
	tx_char(0x0D);
	tx_char(0x0A);
	while(rx_char()!='O');
	while(rx_char()!='K');
	if(n<10)
	{
		tx_str("AT+CIPSEND=19");
		tx_char(0x0D);
		tx_char(0x0A);
		while(rx_char()!='>');
		
		tx_str("GET /1.php?temp=");
		tx_char(num[0]);
		tx_char(0x0D);
		tx_char(0x0A);
		while(rx_char()!='O');
		while(rx_char()!='K');
		delay(500);
		tx_str("AT+CIPCLOSE");
		tx_char(0x0D);
		tx_char(0x0A);
	}
	else if(n<100 && n>=10)
	{
		tx_str("AT+CIPSEND=20");
		tx_char(0x0D);
		tx_char(0x0A);
		while(rx_char()!='>');
		tx_str("GET /1.php?temp=");
		tx_char(num[0]);
		tx_char(num[1]);
		tx_char(0x0D);
		tx_char(0x0A);
		while(rx_char()!='O');
		while(rx_char()!='K');
		delay(500);
		tx_str("AT+CIPCLOSE");
		tx_char(0x0D);
		tx_char(0x0A);
	}
	else if(n<1000 && n>=100)
	{
		tx_str("AT+CIPSEND=21");
		tx_char(0x0D);
		tx_char(0x0A);
		while(rx_char()!='>');
		tx_str("GET /1.php?temp=");
		tx_char(num[0]);
		tx_char(num[1]);
		tx_char(num[2]);
 		tx_char(0x0D);
		tx_char(0x0A);
		while(rx_char()!='O');
		while(rx_char()!='K');
		delay(500);
		tx_str("AT+CIPCLOSE");
		tx_char(0x0D);
		tx_char(0x0A);
	}
}



void delay(int x)
{
	int i,j;
	for(i=0;i<x;i++)
	{
		for(j=0;j<1275;j++);
	} 
}




void tx_char(unsigned char val)
{
	SBUF=val;
	while(TI==0);
	TI=0;
}



void tx_str(unsigned char *disp)
{
	int x=0;
	while(disp[x]!='\0')
	{
		tx_char(disp[x]);
		x=x+1;
	}
}



unsigned char rx_char()
{
	while(RI==0);
	RI=0;
	return SBUF;
}



void convert(unsigned int z)
{
	int m,x,y;
	x=y=z;
	for(i=0;i<4;i++)
	{
		x=x/10;
		if(x==0)
		{
			break;
		}
	}
	m=i;
	for(j=0;j<i;j++)
	{
		num[m]=48+(y%10);
		y=y/10;
		m--;
	}
	num[0]=48+y;
	num[i+1]='\0';
}

