using UnityEngine;
using System.Collections;

public class SendNotification : MonoBehaviour {

	public string message;
	public GameObject sendTo;

	void OnTriggerEnter2D(Collider2D other)
	{
		sendTo.GetComponent<Notification>().SetNotification(message);
		Destroy(gameObject);
	}
}
