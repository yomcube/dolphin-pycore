"""
Module for awaiting or registering callbacks on all events emitted by Dolphin.

The odd-looking Protocol classes are just a lot of syntax to essentially describe
the callback's signature. See https://www.python.org/dev/peps/pep-0544/#callback-protocols
"""
from collections.abc import Callable
from typing import Protocol, type_check_only


def on_frameadvance(callback: Callable[[], None] | None) -> None:
    """Registers a callback to be called every time the game has rendered a new frame."""


async def frameadvance() -> None:
    """Awaitable event that completes once the game has rendered a new frame."""
	

def on_framebegin(callback: Callable[[], None] | None) -> None:
    """Registers a callback to be called every time the game checks for controller inputs.
		Typically happen twice per frame, before and after frameadvance.
		Should be used for performing inputs on a specific frame """


async def framebegin() -> None:
    """Awaitable event that completes once the game checks for controller inputs."""



@type_check_only
class _CodebreakpointCallback(Protocol):
    def __call__(self, addr: int) -> None:
        """
        Example callback stub for on_codebreakpoint.

        :param addr: address that was accessed
        """


def on_codebreakpoint(callback: _CodebreakpointCallback | None) -> None:
    """
    Registers a callback to be called every time a previously added code breakpoint is hit.

    :param callback:
    :return:
    """


async def codebreakpoint() -> tuple[int,]:
    """Awaitable event that completes once a previously added code breakpoint is hit."""


@type_check_only
class _MemorybreakpointCallback(Protocol):
    def __call__(self, is_write: bool, addr: int, value: int) -> None:
        """
        Example callback stub for on_memorybreakpoint.

        :param is_write: true if a value was written, false if it was read
        :param addr: address that was accessed
        :param value: new value at the given address
        """


def on_memorybreakpoint(callback: _MemorybreakpointCallback | None) -> None:
    """
    Registers a callback to be called every time a previously added memory breakpoint is hit.

    :param callback:
    :return:
    """


async def memorybreakpoint() -> tuple[bool, int, int]:
    """Awaitable event that completes once a previously added memory breakpoint is hit."""


@type_check_only
class _SaveStateCallback(Protocol):
    def __call__(self, is_slot: bool, slot: int, /) -> None:
        """
        Example callback stub for on_savestatesave and/or on_savestateload.

        :param is_slot: true if save/load was with a savestate slot, \
            false if save/load was from a file
        :param slot: the slot the save/load occurred to/from. \
            Should be disregarded if is_slot is false
        """


def on_savestatesave(callback: _SaveStateCallback | None) -> None:
    """
    Registers a callback to be called every time a savestate is saved.

    :param callback:
    :return:
    """


async def savestatesave() -> tuple[bool, int]:
    """Awaitable event that completes once a savestate is saved."""


def on_savestateload(callback: _SaveStateCallback | None) -> None:
    """
    Registers a callback to be called every time a savestate has been loaded.

    :param callback:
    :return:
    """


async def savestateload() -> tuple[bool, int]:
    """Awaitable event that completes once a savestate has been loaded."""
	
	
	
def on_beforesavestateload(callback: _SaveStateCallback | None) -> None:
    """
    Registers a callback to be called before a savestate is been loaded.

    :param callback:
    :return:
    """


async def beforesavestateload() -> tuple[bool, int]:
    """Awaitable event that completes before a savestate is been loaded."""



@type_check_only
class _BoolCallback(Protocol):
    def __call__(self, boolean: bool) -> None:
        """
        Example callback stub for on_focuschange.

        :param boolean: correspond to the has_focus state \
		or other boolean depending on the context
        """
		
def on_unpause(callback: Callable[[], None] | None) -> None:
    """
    Registers a callback to be called on emulation unpause.

    :param callback:
    :return:
    """


async def unpause() -> None:
    """Awaitable event that completes on emulation unpause."""



def on_focuschange(callback: _BoolCallback | None) -> None:
    """
    Registers a callback to be called on render window focus change.

    :param callback:
    :return:
    """


async def focuschange() -> bool:
    """Awaitable event that completes on render window focus change."""

@type_check_only
class _GeometryCallback(Protocol):
    def __call__(self, x: int, y:int, width:int, height:int) -> None:
        """
        Example callback stub for rendergeometrychange.

        :param x: x coordinate of the window
		:param y: y coordinate of the window
		:param width: width of the window
		:param height: height of the window
        """

def on_rendergeometrychange(callback: _GeometryCallback | None) -> None:
    """
    Registers a callback to be called on render window geometry change.

    :param callback:
    :return:
    """


async def rendergeometrychange() -> tuple[int, int, int, int]:
    """Awaitable event that completes on render window geometry change."""
	
	
def on_timertick(callback: Callable[[], None] | None) -> None:
    """Registers a callback to be called 60 times per second"""


async def frameadvance() -> None:
    """Awaitable event that completes 60 times per second"""
	
	
def system_reset() -> None:
    """Resets the emulation."""
