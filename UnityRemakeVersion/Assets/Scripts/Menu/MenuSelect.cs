using UnityEngine;
using System.Collections;

public class MenuSelect : MonoBehaviour {

	public GameObject bigEye;
	public GameObject fade;
	public AudioSource music;

	bool fadeOut = false;
	float dt;
	float volume = 1;

	// Use this for initialization
	void Start () {
		Screen.showCursor = true;
		fade.GetComponent<SpriteRenderer>().color = new Color(1f,1f,1f,0);
	}
	
	// Update is called once per frame
	void Update () {

		if(!fadeOut)
		{
			if (Input.GetMouseButtonDown(0))
			{
				RaycastHit2D hit = Physics2D.Raycast(Camera.main.ScreenToWorldPoint(Input.mousePosition), Vector2.zero);

				if(hit.collider != null)
				{
					if(hit.collider.gameObject.name == "titlePlay")
						fadeOut = true;
						
					if(hit.collider.gameObject.name == "titleExit")
						Application.Quit();
				}
			}

			RaycastHit2D hitHover = Physics2D.Raycast(Camera.main.ScreenToWorldPoint(Input.mousePosition), Vector2.zero);
			
			if(hitHover.collider != null)
			{
				if(hitHover.collider.gameObject.name == "titlePlay")
					bigEye.GetComponent<Point_AB_Switch>().MoveToPointOne();
				
				if(hitHover.collider.gameObject.name == "titleExit")
					bigEye.GetComponent<Point_AB_Switch>().MoveToPointTwo();
			}
		}
		else
		{
			dt += Time.deltaTime;
			volume -= Time.deltaTime;

			if(dt < 1)
			{
				fade.GetComponent<SpriteRenderer>().color = new Color(1f,1f,1f,dt);
				music.volume = volume;
			}
			else 
			{
				Screen.showCursor = false;

				PlayerPrefs.SetInt("SeenIntro", 1);

				if(this.GetComponent<SkipIntro>().skip)
					Application.LoadLevel("Tutorial_Level1");
				else
					Application.LoadLevel("Story_Intro");

			}
		}
	}
}
