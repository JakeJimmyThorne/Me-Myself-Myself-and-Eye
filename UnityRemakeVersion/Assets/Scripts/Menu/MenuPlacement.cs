using UnityEngine;
using System.Collections;

public class MenuPlacement : MonoBehaviour {

	int width = Screen.width;
	int height = Screen.height;

	public GameObject title;

	// Use this for initialization
	void Start () {
		title.transform.position = new Vector3(width / 200 - 0.5f,
		                                       height / 200,
		                                       0);
	}
	
	// Update is called once per frame
	void Update () {
	
	}
}
