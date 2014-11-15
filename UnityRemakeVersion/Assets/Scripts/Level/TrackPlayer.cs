using UnityEngine;
using System.Collections;

public class TrackPlayer : MonoBehaviour {

	public GameObject player;
	public GameObject eye;

	// Use this for initialization
	void Start () {
	
	}
	
	// Update is called once per frame
	void Update () {

		float f_angle = Mathf.Atan2((transform.position.x - player.transform.position.x),
		                             transform.position.y - player.transform.position.y);
		
		Vector2 velocity = -new Vector2(Mathf.Sin(f_angle),
		                               Mathf.Cos(f_angle));

		RaycastHit2D hit = Physics2D.Raycast(transform.position, velocity,0.5f);

		eye.transform.position = transform.position + new Vector3(velocity.x, velocity.y,-0.1f) / 9;
	
	}
}
