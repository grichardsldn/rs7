// This is a test device

class DrumChannel
{
	public:
	signed short *data;
	int current;
	int length;
	void Trigger( );
	void Stop( );
	bool Load( const char *filename );
	signed short Clock();

	DrumChannel();
};

class DeviceSampDrum : public IDevice
{
	public:

	// IDevice stuff
	virtual void Init( 	IDeviceEvents *event,
				const char *instance_name, 
				int samplerate,
				const char *startup_params );
	virtual bool SetOutput( const char *output_name, int *output_ptr );
	virtual void Clock();
	virtual void MidiNoteOn( int channel, int note, int volume );
	virtual void MidiNoteOff( int channel, int note );
	virtual bool SetMidiInput( const char *input, int channel );

	DeviceSampDrum();

	private:
	int channel;
	DrumChannel *channels[10];
	bool allocated[10];
	int note_numbers[10];
	int *output_ptrs[10];
	bool initialised;
};

