using UnityEngine;
using System.Collections;

public class Goal : MonoBehaviour {

	const int MAX_HEADS = 3;

	public GameObject[] headList = new GameObject[MAX_HEADS];

	public int collectedCount = 0;
	public int toCollect = 0;

	public Sprite goalOpened;

	public bool opened = false;
	public string nextLevel;

	bool init_open = true;

	// Use this for initialization
	void Start () {

		for(int i = 0; i < MAX_HEADS; i++)
		{
			if(headList[i] != null)
				toCollect++;
		}
	}
	
	// Update is called once per frame
	void Update () {

		if(collectedCount == toCollect)
			opened = true;

		for(int i = 0; i < MAX_HEADS; i++)
		{
			if(headList[i] != null)
			{
				if(headList[i].GetComponent<HeadCollect>().collected)
				{
					collectedCount++;
					headList[i] = null;
					return;
				}
			}
		}
	
		if(opened)
		{
			if(init_open)
			{
				this.GetComponent<SpriteRenderer>().sprite = goalOpened;
				init_open = false;
			}
		}
	}

	void OnCollisionEnter2D(Collision2D coll)
	{
		if(opened)
		{
			Application.LoadLevel(nextLevel);
		}
	}
}
