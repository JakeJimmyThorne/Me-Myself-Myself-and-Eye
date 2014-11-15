using UnityEngine;
using System.Collections;

public class SkipIntro : MonoBehaviour {

	public bool skip = false;
	public Vector2 position;

	public bool resetPlayerSave = true;

	// Use this for initialization
	void Start () {
	
		if(PlayerPrefs.GetInt("SeenIntro") == 1)
			skip = true;

		if(resetPlayerSave)
		{
			PlayerPrefs.DeleteAll();
			skip = false;
		}
	}

	void OnGUI()
	{
		skip = GUI.Toggle(new Rect(position.x, 
		                           position.y, 80, 50), skip, "Skip Intro");

	}
	
	// Update is called once per frame
	void Update () {
	
	}
}
