class DoorMan(val base: Array[Array[Char]]) {
  var state: Array[Array[Char]] = base.clone()
  private val doors: Array[Door] = Array(new Door('A'), new Door('B'), new Door('C'))
  setIndicators()

  def setIndicators(): Unit = {

    for {
      (cur, offset) <- List((0, 0), (1, 12), (2, 24))
    } yield {
      {
        state(0)(offset) = ' '
        state(0)(offset + 11) = ' '
      }
    }
  }

  def reset(): Unit = {
    for (door <- doors) door.reset()
    set(Array[String]("0","0","0"), 102.1f)
    state = base
    setIndicators()
  }

  def set(readings: Array[String], powerIncrement: Float): Array[Int] = {
    val array: Array[Int] = Array(0, 0, 0)
    for ((door, i) <- doors.zipWithIndex) {
      array(i) = door.set(10 - (readings(i).toInt / powerIncrement).toInt)
      val offset = getOffset(i)

      for (i <- 0 to 9) {
        if (i < door.maxSlide - door.slide) {
          state(1)(i + offset) = ' '
        } else {
          state(1)(i + offset) = '='
        }
      }

      for (i <- 0 to 7) {
        if (i < door.maxStock - door.stock) {
          state(0)(i + offset + 1) = ' '
        }else {
          state(0)(i + offset + 1) = door.charType
        }
      }
    }
    array
  }

  def getDoor(i: Int): Door = {
    doors(i)
  }

  def getOffset(i: Int): Int = i match {
    case 0 => 1
    case 1 => 13
    case 2 => 25
  }
}