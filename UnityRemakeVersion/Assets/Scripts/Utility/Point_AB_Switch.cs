using UnityEngine;
using System.Collections;

public class Point_AB_Switch : MonoBehaviour {

	public Vector2 pointOne;
	public Vector2 pointTwo;

	public float speed;

	Vector3 currentPos;
	Vector3 targetPos;

	// Use this for initialization
	void Start () {
		targetPos = pointOne;
	}
	
	// Update is called once per frame
	void Update () {
	
		currentPos = this.transform.position;

//		if(currentPos.x < targetPos.x && currentPos.y > targetPos.y
//
//
//		   && targetPos.x == pointOne.x)
//		{
//			float f_angle = Mathf.Atan2(currentPos.y - targetPos.y,
//			                            currentPos.x - targetPos.x);
//			
//			Vector3 velocity = new Vector3(Mathf.Cos(f_angle),
//			                       		   Mathf.Sin(f_angle),
//			                       		   0);
//
//			this.transform.position += velocity * speed;
//		}

	}

	public void MoveToPointOne()
	{
		targetPos = pointOne;

		if(Mathf.Abs (currentPos.x - targetPos.x) + Mathf.Abs(currentPos.y - targetPos.y) > 0.1f)
		{
			float f_angle = Mathf.Atan2(currentPos.y - targetPos.y,
			                            currentPos.x - targetPos.x);
			
			Vector3 velocity = -new Vector3(Mathf.Cos(f_angle),
			                                Mathf.Sin(f_angle),
			                                0);
			
			this.transform.position += velocity * speed;
		}
	}

	public void MoveToPointTwo()
	{
		targetPos = pointTwo;

		if(Mathf.Abs (currentPos.x - targetPos.x) + Mathf.Abs(currentPos.y - targetPos.y) > 0.1f)
		{
			float f_angle = Mathf.Atan2(currentPos.y - targetPos.y,
			                            currentPos.x - targetPos.x);
			
			Vector3 velocity = -new Vector3(Mathf.Cos(f_angle),
			                       		   Mathf.Sin(f_angle),
			                       		   0);

			this.transform.position += velocity * speed;
		}
	}
}
