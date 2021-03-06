#include <stdio.h>
#include "../IDevice.h"
#include <assert.h>
#include <string.h>
#include <stdlib.h>

#include <pthread.h>
#include "../darkbat/dkb.h"
#include "vol.h"
#include "../settings.h"


#include "../ui/Panel.h"
#include "mixer.h"

static int nowhere = 0;

void DeviceMixer::Init( IDeviceEvents *event,
			const char *instance_name,
			int samplerate,
			const char *startup_params)
{
	char name[1024];
	printf( "instance=%s\n", instance_name);
	sprintf( &name[0], "%s.set", instance_name);
	printf( "instance=%s\n", name);
	x = 0; y =0; z = 0;
	settings = new Settings( name );
	settings->AddSetting( "x", &x );
	settings->AddSetting( "y", &y );
	settings->AddSetting( "z", &z );
	printf( "y=%d\n", y );
	// dont care about any of these
	//vol_panel = new VolPanel();
	//vol_panel = new VolPanel(x,y,z);
	for( int i = 0 ; i < NUM_INPUTS ; i ++ )
	{
		char sname[100];
		sprintf( &sname[0], "chvol%d", i );
		volumes[i] = 0;
		settings->AddSetting( sname, &volumes[i] );
	}
	out_left = &nowhere;
	out_right = &nowhere;	
	settings->Read();
	settings->Write();
	CreatePanel();
}
void DeviceMixer::Event( int ref, int key )
{
	settings->Write();
}

void DeviceMixer::CreatePanel()
{
        int w= (NUM_INPUTS * 3) + 4 + 3;
        int h = 14;
        panel = Panel::CreatePanel();
        panel->SetPos( x,y,z );
        panel->SetZ(5);
        panel->AddLine( 100, 0,0, w, 0 );
        panel->AddLine( 101, w,0, w, h );
        panel->AddLine( 102, w,h, 0, h );
        panel->AddLine( 103, 0,h, 0, 0 );
        panel->SetZ(0);

	int end_x;
	for( int i = 0 ; i < NUM_INPUTS ; i ++ )
	{
		int xpos = 2 + ( i * 3 );
        	panel->AddVSlider(104+i, xpos, 2, 10, &volumes[i],0 );
		end_x = xpos;
	}
	panel->AddButton( 200, end_x + 3, 2, this );
}
	
void DeviceMixer::Clock()
{
	int val;

	for( int i = 0 ; i < NUM_INPUTS ; i++)
	{
		int ch_val = 0;
		if( inputs[i] != NULL )
		{	
			ch_val = (*inputs[i] / 20 * volumes[i]);	
			val += ch_val;
			if(  post_fader_outs[i] != NULL )
			{		
			//	*post_fader_outs[i] = ch_val;
			}
		}
	}
	if( val >2000000000  )	
	{
		val = 2000000000;;
	}
	if( val < -2000000000)
	{
		val = -2000000000;
	}
	/*
	if( val >8388600  )	
	{
		val == 8388600;;
	}
	if( val < 8388600)
	{
		val = -8388600;
	}*/

	if( out_left != NULL ) *out_left = val;
	if( out_right != NULL ) *out_right = val;
}


bool DeviceMixer::SetInput( const char *input_name, int *input_ptr )
{
	int index = -1;
	if( ( input_name[0] == 'c') && (input_name[1] == 'h') );
	{
		int num = atoi( input_name + 2 );
		inputs[ num - 1] = input_ptr;
	}
	return true;
}

bool DeviceMixer::SetOutput( const char *output_name, int *output_ptr)
{
	assert( output_name );
	assert( output_ptr );

	if( strcmp( "left", output_name) == 0 )
	{
		out_left = output_ptr;
	}
	else if( strcmp( "right", output_name) == 0 )
	{
		out_right = output_ptr;
	}
	else if( output_name[0] == 'a' )
	{
		int num = atoi( output_name + 1 );
		if( num > 0 )
		{
			post_fader_outs[num - 1] = output_ptr;	
		}
	}
	else
	{
		printf("DeviceMixer: Output %s unknown\n",
			output_name);
		return false;
	} 
	return true;
}	
		

DeviceMixer::DeviceMixer()
{
	for( int i = 0 ; i < NUM_INPUTS; i++)
	{
		inputs[i] = NULL;
		post_fader_outs[i] = NULL;
	}
	out_left = NULL;
	out_right = NULL;
}
