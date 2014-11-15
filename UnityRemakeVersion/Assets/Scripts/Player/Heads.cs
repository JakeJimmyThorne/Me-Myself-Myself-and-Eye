using UnityEngine;
using System.Collections;

public class Heads : MonoBehaviour {

	//Scene heads
	public GameObject headOne, headTwo, headThree;
	public Sprite idleHeadTexture, leftHeadTexture, rightHeadTexture;

	const int MAX_HEADS = 3;
	GameObject[] heads = new GameObject[MAX_HEADS];

	float[] idleY = new float[MAX_HEADS];
	float[] idleX = new float[MAX_HEADS];

	bool showHeadOne = true;
	bool showHeadTwo = false;
	bool showHeadThree = false;

	public void MoveLeft(Vector3 playerPos)
	{
		headOne.transform.position = playerPos + new Vector3(0.02f,idleY[0],0);
		headTwo.transform.position = playerPos + new Vector3(0.04f,idleY[1],0);
		headThree.transform.position = playerPos + new Vector3(0.06f,idleY[2],0);
	}

	public void MoveRight(Vector3 playerPos)
	{
		headOne.transform.position = playerPos + new Vector3(-0.02f,idleY[0],0);
		headTwo.transform.position = playerPos + new Vector3(-0.04f,idleY[1],0);
		headThree.transform.position = playerPos + new Vector3(-0.06f,idleY[2],0);
	}

	public void Idle(Vector3 playerPos)
	{
		headOne.transform.position = playerPos + new Vector3(idleX[0],idleY[0],0);
		headTwo.transform.position = playerPos + new Vector3(idleX[1],idleY[1],0);
		headThree.transform.position = playerPos + new Vector3(idleX[2],idleY[2],0);
	}

	void AddHead()
	{
		if(showHeadTwo)
		{
			showHeadThree = true;
			headThree.SetActive(true);
		}
		else 
		{
			showHeadTwo = true;
			headTwo.SetActive(true);
		}
	}

	// Use this for initialization
	void Start () 
	{
		idleY[0] = 0.3f;
		idleY[1] = 0.6f;
		idleY[2] = 0.9f;

		headTwo.SetActive(false);
		headThree.SetActive(false);
	}
	
	// Update is called once per frame
	void Update () 
	{
		
	}
}
