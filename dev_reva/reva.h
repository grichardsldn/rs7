
class RevADelay;

#define NUM_DELAY_SETTINGS (100 )

class DeviceRevA : public IDevice
{
	public:

	// IDevice stuff
	virtual void Init( 	IDeviceEvents *event,
				const char *instance_name, 
				int samplerate,
				const char *startup_params );
	virtual bool SetOutput( const char *output_name, int *output_ptr );
	virtual bool SetInput( const char *input_name, int *input_ptr );
	virtual void Clock();
	virtual void MidiNoteOn( int channel, int note, int volume );
	virtual void MidiNoteOff( int channel, int note );
	virtual bool SetMidiInput( const char *input, int channel );
	virtual bool SetMidiOutput( const char *output, int channel );

	DeviceRevA();

	private:
	RevADelay *delay;
	int *input_ptr;
	int *output_ptr;
	int delay_times[NUM_DELAY_SETTINGS];
	signed short delay_amounts[NUM_DELAY_SETTINGS];	
	int last;
	int tick;
	int change;
};

