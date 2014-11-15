using UnityEngine;
using System.Collections;

public class HeadCollect : MonoBehaviour {

	public bool collected = false;

	void OnTriggerEnter2D(Collider2D other)
	{
		other.GetComponent<Heads>().BroadcastMessage("AddHead");
		collected = true;

		GetComponent<SpriteRenderer>().enabled = false;
		GetComponent<BoxCollider2D>().enabled = false;
		//Destroy (gameObject);
	}
}
