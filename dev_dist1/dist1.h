

class Setting;
class Panel;

class DeviceDist1 : public IDevice, PanelBtnEvRx
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

	// PanelBtnEvRx stuff
	virtual void Event( int ref, int key );

	// class stuff
	DeviceDist1();

	private:
	Settings *settings;
	Panel *panel;
	int x_setting;
	int y_setting;
	int z_setting;
	int pre_setting;
	int post_setting;
	int level_setting;
	int engage_setting;
	int *input_ptr;
	int *output_ptr;
};

