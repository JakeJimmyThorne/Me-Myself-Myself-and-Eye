using UnityEngine;
using System.Collections;

public class Notification : MonoBehaviour {
	
	public Vector2 position;
	public Vector2 size;
	public int fontSize = 20;
	
	public float fadeTime;
	
	private bool showNotification = false;
	
	private string notificationText = "";
	public float dt;
	
	private GUIStyle style = new GUIStyle();
	
	void Start()
	{
		style.normal.textColor = Color.white;
		style.fontSize = fontSize;
	}
	
	void Update()
	{
		if(showNotification)
		{
			dt += Time.deltaTime;
			
			if(dt > fadeTime)
			{
				showNotification = false;
				notificationText = "";
			}
		}
	}
	
	public void SetNotification(string newMessage)
	{
		notificationText += "\n" + newMessage;
		
		showNotification = true;
		dt = 0;
	}
	
	void SetError(string newMessage)
	{
		notificationText += "\nERROR: " + newMessage;
		
		showNotification = true;
		dt = 0;
	}
	
	void OnGUI()
	{
		if(showNotification)
		{
			// GUI.Label(new Rect(positionFromBottomLeft.x,
			// 				   Screen.height - positionFromBottomLeft.y,
			// 				   size.x,
			// 				   size.y), notificationText, style);
			
			GUI.TextArea(new Rect(position.x,
			                      position.y,
			                      size.x,
			                      size.y), notificationText, style);
		}
	}
}

