using UnityEngine;
using System.Collections;

public class CameraManager : MonoBehaviour {

	public Camera TopLeft;
	public Camera TopRight;

	public Camera BottomLeft;
	public Camera BottomRight;

	Vector3 TL_Position = new Vector3(-4.447368f,2.503164f,-10);
	Vector3 TR_Position = new Vector3(4.447368f,2.503164f,-10);

	Vector3 BL_Position = new Vector3(-4.447368f,-2.503164f,-10);
	Vector3 BR_Position = new Vector3(4.447368f,-2.503164f,-10);

	Rect TL_Rect = new Rect(-0.5f,0.5f,1,1);
	Rect TR_Rect = new Rect(0.5f,0.5f,1,1);

	Rect BL_Rect = new Rect(-0.5f,-0.5f,1,1);
	Rect BR_Rect = new Rect(0.5f,-0.5f,1,1);

	public enum Position {TOP_LEFT, TOP_RIGHT, BOTTOM_LEFT, BOTTOM_RIGHT};
	//public enum Rotation {ZERO,NINTY,ONE_EIGHTY,TWO_SEVENTY};

	public enum Rotation
	{
		ZERO = 0,
		NINTY = 90,
		ONE_EIGHTY = 180,
		TWO_SEVENTY = 270
	}

	public Position topLeftCam = Position.TOP_LEFT;
	public Position topRightCam = Position.TOP_RIGHT;
	public Position bottomLeftCam = Position.BOTTOM_LEFT;
	public Position bottomRightCam = Position.BOTTOM_RIGHT;

	public Rotation topLeftRot = Rotation.ZERO;
	public Rotation topRightRot = Rotation.ZERO;
	public Rotation bottomLeftRot = Rotation.ZERO;
	public Rotation bottomRightRot = Rotation.ZERO;


	// Use this for initialization
	void Start () {

		switch(topLeftCam)
		{
		case Position.TOP_LEFT:
			TopLeft.transform.position = TL_Position;
			//TopLeft.rect = TL_Rect;
			Debug.Log ("TO TOP LEFT");
			break;
		case Position.TOP_RIGHT:
			TopLeft.transform.position = TR_Position;
			//TopLeft.rect = TR_Rect;
			Debug.Log ("TO TOP RIGHT");
			break;
		case Position.BOTTOM_LEFT:
			TopLeft.transform.position = BL_Position;
			//TopLeft.rect = BL_Rect;
			Debug.Log ("TO BOTTOM LEFT");
			break;
		case Position.BOTTOM_RIGHT:
			TopLeft.transform.position = BR_Position;
			//TopLeft.rect = BR_Rect;
			Debug.Log ("TO BOTTOM RIGHT");
			break;
		}

		switch(topRightCam)
		{
		case Position.TOP_LEFT:
			TopRight.transform.position = TL_Position;
			//TopRight.rect = TL_Rect;
			Debug.Log ("TO TOP LEFT");
			break;
		case Position.TOP_RIGHT:
			TopRight.transform.position = TR_Position;
			//TopRight.rect = TR_Rect;
			Debug.Log ("TO TOP RIGHT");
			break;
		case Position.BOTTOM_LEFT:
			TopRight.transform.position = BL_Position;
		    //TopRight.rect = BL_Rect;
			Debug.Log ("TO BOTTOM LEFT");
			break;
		case Position.BOTTOM_RIGHT:
			TopRight.transform.position = BR_Position;
			//TopRight.rect = BR_Rect;
			Debug.Log ("TO BOTTOM RIGHT");
			break;
		}

		switch(bottomLeftCam)
		{
		case Position.TOP_LEFT:
			BottomLeft.transform.position = TL_Position;
			//BottomLeft.rect = TL_Rect;
			Debug.Log ("TO TOP LEFT");
			break;
		case Position.TOP_RIGHT:
			BottomLeft.transform.position = TR_Position;
			//BottomLeft.rect = TR_Rect;
			Debug.Log ("TO TOP RIGHT");
			break;
		case Position.BOTTOM_LEFT:
			BottomLeft.transform.position = BL_Position;
			//BottomLeft.rect = BL_Rect;
			Debug.Log ("TO BOTTOM LEFT");
			break;
		case Position.BOTTOM_RIGHT:
			BottomLeft.transform.position = BR_Position;
			//BottomLeft.rect = BR_Rect;
			Debug.Log ("TO BOTTOM RIGHT");
			break;
		}

		switch(bottomRightCam)
		{
		case Position.TOP_LEFT:
			BottomRight.transform.position = TL_Position;
			//BottomRight.rect = TL_Rect;
			Debug.Log ("TO TOP LEFT");
			break;
		case Position.TOP_RIGHT:
			BottomRight.transform.position = TR_Position;
			//BottomRight.rect = TR_Rect;
			Debug.Log ("TO TOP RIGHT");
			break;
		case Position.BOTTOM_LEFT:
			BottomRight.transform.position = BL_Position;
			//BottomRight.rect = BL_Rect;
			Debug.Log ("TO BOTTOM LEFT");
			break;
		case Position.BOTTOM_RIGHT:
			BottomRight.transform.position = BR_Position;
			//BottomRight.rect = BR_Rect;
			Debug.Log ("TO BOTTOM RIGHT");
			break;
		}

		TopLeft.transform.Rotate(new Vector3(0,0,(float)topLeftRot));
		TopRight.transform.Rotate(new Vector3(0,0,(float)topRightRot));
		BottomLeft.transform.Rotate(new Vector3(0,0,(float)topLeftRot));
		BottomRight.transform.Rotate(new Vector3(0,0,(float)bottomLeftRot));
	}
	
	// Update is called once per frame
	void Update () {
	
	}
}
