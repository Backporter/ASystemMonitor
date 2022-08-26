	class ASystemMonitor extends MovieClip
{
	var FrameRateHUDString:TextField;
	var loading:Boolean;
	var FrameTime:Number;
	var FrameDelta:Number;
	var FrameDeltaTime:Number;
	var FrameRate:Number;
	
	function ASystemMonitor()
	{
		super();
		loading = true;
		SetFrameRateHUDString("FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF");
		FrameTime = 0;
		FrameDelta = 0;
		FrameDeltaTime = 0;
		FrameRate = 0;
		
		this._x = 961;
		this._y = 1040;
		this._rotation = 0;
		this._xscale = 75;
		this._yscale = 75;
	}
	
	public function setLocation(xpos: Number, ypos: Number, rot: Number, xscale: Number, yscale: Number): Void
	{
		this._x = xpos;
		this._y = ypos;
		this._rotation = rot;
		this._xscale = xscale;
		this._yscale = yscale;
	}
	
	public function SetFrameTime(aFrameTime:Number):Void
	{
		FrameTime = aFrameTime;
	}
	
	public function SetFrameDelta(aFrameDelta:Number):Void
	{
		FrameDelta = aFrameDelta;
	}
	
	public function SetFrameDeltaTime(aFrameDeltaTime:Number):Void
	{
		FrameDeltaTime = aFrameDeltaTime;
	}
	
	public function CreateFrameString()
	{
		FrameRateHUDString.text = "FrameRate: " + String(FrameRate);
	}
	
	public function SetFrameRate(aFrameRate:Number):Void
	{
		FrameRate = aFrameRate;
		CreateFrameString();
	}
	
	public function SetFrameRateHUDString(aFrameRateHUDString:String):Void
	{
		aFrameRateHUDString != undefined ? FrameRateHUDString.text = aFrameRateHUDString : FrameRateHUDString.text = "";
	}

}