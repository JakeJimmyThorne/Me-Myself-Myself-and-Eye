﻿using UnityEngine;
using System.Collections;

public class KillBoundaries : MonoBehaviour {

	void OnTriggerEnter2D(Collider2D other)
	{
		Application.LoadLevel(Application.loadedLevel);
	}
}
