using UnityEngine;
using System.Collections;
using System.Collections.Generic;

public class StoryShowreel : MonoBehaviour {

	public List<Sprite> storyPanels = new List<Sprite>();
	public List<float> panelShowTime = new List<float>();
	public List<bool> zoomIn = new List<bool>();
	public List<Vector3> zoomSpeed = new List<Vector3>();

	float dt;
	public bool start;

	int iteration = 0;

	int count;

	// Use this for initialization
	void Start () {
		count = storyPanels.Count;

		this.GetComponent<SpriteRenderer>().sprite = storyPanels[0];
	}
	
	// Update is called once per frame
	void Update () {

		if(start)
		{
			dt += Time.deltaTime;

			if(dt > panelShowTime[iteration])
			{
				iteration++;

				if(iteration < count)
				{
					this.transform.localScale = new Vector3(1,1,1);

					this.GetComponent<SpriteRenderer>().sprite = storyPanels[iteration];
					dt = 0;
				}
				else 
				{
					Application.LoadLevel("Tutorial_Level1");
					start = false;
					return;
				}
			}

			if(zoomIn[iteration])
			{
				this.transform.localScale += zoomSpeed[iteration];
			}
		}
	}
}
