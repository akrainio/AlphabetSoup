class DoorMan(val base: Array[Array[Char]]) {
  var state: Array[Array[Char]] = base.clone()
  private val doors: Array[Door] = Array(new Door('A'), new Door('B'), new Door('C'))
  private var selected = 1
  setIndicators()

  def next(): Unit = {
    selected += 1
    if (selected > 2) selected = 0
    setIndicators()
  }

  def prev(): Unit = {
    selected -= 1
    if (selected < 0) selected = 2
    setIndicators()
  }

  def setIndicators(): Unit = {
    for {
      (cur, offset) <- List((0, 0), (1, 12), (2, 24))
    } yield {
      if (cur == selected) {
        state(0)(offset) = '>'
        state(0)(offset + 11) = '<'
      } else {
        state(0)(offset) = ' '
        state(0)(offset + 11) = ' '
      }
    }
  }

  def  reset(): Unit = {
    for (door <- doors) door.reset()
    selected = 0
    set(10)
    selected = 2
    set(10)
    selected = 1
    set(10)
    state = base

    setIndicators()
  }

  def set(value: Int): Int = {
    val door = doors(selected)
    val stock = door.set(value)
    val offset = getOffset
    for (i <- 0 to 9) {
      if (i < door.slide) {
        state(1)(i + offset) = '='
      } else {
        state(1)(i + offset) = ' '
      }
    }
    for (i <- 0 to 7) {
      if (i > door.stock - 2) {
        state(0)(i + offset + 1) = ' '
      } else {
        state(0)(i + offset + 1) = door.charType
      }
    }
    stock
  }

  def getDoor: Door = {
    doors(selected)
  }

  def getOffset: Int = selected match {
    case 0 => 1
    case 1 => 13
    case 2 => 25
  }
}