import com.greensock.*;

// by osmosis-wrench 2022
class AshOfWar extends MovieClip
{
	var ashText: TextField;
	var textPosBaseX: Number;
	var textPosBaseY: Number;
	
	public function AshOfWar() {
		super();
		ashText.autoSize = "left"; // allow the textbox to grow larger to the right.
		textPosBaseX = this.ashText._x;
		textPosBaseY = this.ashText._y;
		//setLocation(50, 850, 0, 100, 100, 50, 50);
		setText("myPowerNameText");

	}
	
	public function setLocation(xpos: Number, ypos: Number, rot: Number, xscale: Number, yscale: Number, text_xpos_mod: Number, text_ypos_mod: Number): Void
	{
		this._x = xpos;
		this._y = ypos;
		this._rotation = rot;
		this._xscale = xscale;
		this._yscale = yscale;
		this.ashText._x = textPosBaseX + text_xpos_mod;
		this.ashText._y = textPosBaseY + text_ypos_mod;
		
	}
	
	public function setText(newText: String): Void
	{
		ashText.text = newText;
	}
	
}